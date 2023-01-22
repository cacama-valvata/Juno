#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>


#define BUFSIZE 256
#define INPUTLEN 32

/* 
 * Usernames can only be composed of
 * - lowercase alphabet
 * - numerics
 * - underscore
 */
const char * const allowed_chars = "abcdefghijklmnopqrstuvwxyz0123456789_";

/* 
 * Records current user that we are running commands for
 * Authenticated by SSH server
 */
char* session_user = NULL;

void read_credentials(char *username, char *password)
{
    FILE *file;
    file = fopen("credentials.txt", "r");
    if (file == NULL) {
        printf("Error opening file");
        return;
    }
    fgets(username, INPUTLEN, file);
    fgets(password, INPUTLEN, file);
    fclose(file);
}

void execdb(char *username, char *password, char* query, char* buf)
{

    int pipefd[2];
    pid_t pid;
    int bytes_read; 



    if (pipe(pipefd) == -1)
    {
        perror("pipe");
        return;
    }

    pid = fork();
    if (pid == -1)
    {
        perror("fork");
        return;
    }

    if (pid == 0) 
    {  
        // child process
        close(pipefd[0]);  // close unused read end
        dup2(pipefd[1], STDOUT_FILENO);  // redirect stdout to write end of pipe

        // construct SQL query to check for unique user with this public key

        execl("/usr/bin/mysql", "mysql", "-u", "user", "-p", "password", "-e", query, NULL);
    } 

    else 
    {  
        // parent process
        close(pipefd[1]);
        bytes_read = read(pipefd[0], buf, BUFSIZE);
        if (bytes_read > 0) 
        {
            buf[bytes_read] = '\0';
            printf("%s", buf);
        }
        close(pipefd[0]);
        wait(NULL);
    }
}

void retrieve_conf(char* key, char* username, char* password, char* gameid)
{
    char *query;
    char buf[BUFSIZE];

    query = "SELECT, ready FROM games, where gameid = '";
    query = strcat(query, gameid);
    query = strcat(query, "';");
    execdb(username,password,query, buf);

    //pase buf into simple output

    //IF GAME READY
    if(strcmp(buf,"1") == 0)
    {
        // use exec for WG server
        printf("here is your new config %s", key);
    }

        //no game user must wait
    else
        printf("game has not finished initializing");

    return;
}


void heartbeat (char* key, char* username, char* password)
{
    char *query;
    char buf[BUFSIZE];
    char userid[BUFSIZE];
    char gameid[BUFSIZE];
    char passarg[(strlen(password) + 2)];

    strcat(passarg,"-p");
    strcat(passarg,password);

    //grab user id to search for games
    query = "SELECT, user_id FROM devices, where pubkey = '";
    query = strcat(query, key);
    query = strcat(query, "';");
    execdb(username,passarg,query, buf);

    //parse buf into simple output
    strcpy(userid, buf);

    //search for games w/ user id
    query = "SELECT, game_id FROM game_players, where userid = '";
    query = strcat(query, buf);
    query = strcat(query, "';");
    execdb(username,passarg,query, buf);

    //parse buf into simple output
    strcpy(gameid, buf);
    
    if(buf == NULL)
    {
        printf("NO GAMES");
        return;
    }

    //figure out if game is in the present or past
    query = "SELECT, end_time FROM game,where NOT ENDED & userid = '";
    query = strcat(query, buf);
    query = strcat(query, "';");
    execdb(username,passarg,query, buf);

    //parse buf into simple output

    // IF GAME IS IN THE PAST > MAKE A NEW CONFIG (SOME EXEC MAGIC)
    if(buf == NULL)
    {
        printf("make a new public key");
        return;
    }

    //VERIFY USER KEY
    query = "SELECT, wg_pubkey FROM game_players, userid = '";
    query = strcat(query, userid);
    query = strcat(query, "';");
    execdb(username,passarg,query, buf);

    //if not eequal, update (DONT KNOW HOW)
    if(strcmp(buf,key) != 0)
    {
        query = "UPDATE, wg_pubkey FROM game_players, userid = '";
        query = strcat(query, userid);
        query = strcat(query, "';");
        execdb(username,passarg,query, buf);

        printf("key updated");
        retrieve_conf(key, username, passarg, gameid);
        return;
    }

    //if key is equal generate that sweet sweet config
    else
    {
        printf("key already added!");
        retrieve_conf(key, username, passarg, gameid);
        return;
    }

    return;
}


void wgupdate(char* key)
{
    //sending pub key for config
    printf ("here is my public key %s\n",key);

    char wg_config[4096];

    //use exec to scp generated file
    //print config to standard out
    printf ("here is your config: %s\n", wg_config);

    return;
}


void wgsend()
{
    char user_input[100];
    char concatenated_string[1000] = {0};

    // 'read' file line by line from standard in
    while (1)
    {
        printf ("Enter some text or type stop to end: ");
        fgets (user_input, sizeof(user_input), stdin);

        if (strcmp (user_input, "stop\n") == 0)
            break;

        strcat (concatenated_string, user_input);
    }

    // reconstruct and send to server
    printf ("completed file: %s", concatenated_string);
}

void run_command (char* c)
{
    /*
     * If getenv returns NULL for SSH_ORIGINAL_COMMAND,
     * then it was never set, and this shell wasn't
     * instantiated by the SSH server, just fail.
     */
    if (! c)
        return;

    //grab credentials from auth file for later query
    char username[INPUTLEN], password[INPUTLEN];
    read_credentials(username, password); 

    // each function should check that were logged in!
    
    // copy the argument for tok'ing
    char* command = (char*) calloc (4096, sizeof (char));
    memcpy (command, c, strlen (c));
    // tokenize for (command, arg)
    char* arg = strtok (command, " ");

    if (! strcmp (arg, "heartbeat"))
    {
        arg = strtok (NULL, " ");
        if (! arg)
        {
            free (command);
            return;
        }
        heartbeat (arg, username, password);
    }
    else if (! strcmp(arg, "wgupdate"))
    {
        // grab the argument
        arg = strtok (NULL, " ");
        if (! arg)
        {
            free (command);
            return;
        }
        wgupdate (arg);
    }
    else if (! strcmp(arg, "wgsend"))
    {
        wgsend ();
    }
    else
    {
        printf ("Unknown command.\n");
    }

    // cleanup 
    free (command);
    return;
}

int login (char* c)
{
    // copy the argument for tok'ing
    char* command = (char*) calloc (4096, sizeof (char));
    memcpy (command, c, strlen (c));
    // tokenize for (command, arg)
    char* arg = strtok (command, " ");

    // check that the first command is indeed 'login'
    // as it should be
    if (strcmp (arg, "login"))
    {
        free (command);
        return 1;
    }

    // grab the argument
    arg = strtok (NULL, " ");

    // if there is no arg (no username to set), then fail
    if (! arg)
    {
        free (command);
        return 1;
    }

    // check that the requested username is made up of only allowed characters
    if (strspn (arg, allowed_chars) < strlen (arg))
    {
        free (command);
        return 1;
    }

    // copy username into session_user
    session_user = (char*) calloc (strlen (arg) + 1, sizeof (char));
    memcpy (session_user, arg, strlen (arg));

    // cleanup
    free (command);
    return 0;
}

void cleanup ()
{
    if (session_user)
        free (session_user);
}


int main (int argc, char* argv[]) 
{
    /*
     * If the ssh server and authentication are
     * set up correctly, the shell should always
     * be called non-interactively, and should
     * run the login command before anything else
     */

    // non-interactive commands
    if (argc > 2 && ! strcmp (argv[1], "-c"))
    {
        /* 
         * login() will check that our command is indeed 'login'
         * returns 0 on success
         */
        int r = login (argv[2]);
        // if we failed to login, cleanup and return
        if (r)
        {
            printf ("Authentication failed.");
            cleanup ();
            return 1;
        }
        printf ("Hello, %s.\n", session_user);

        /* 
         * Client would run: ssh host [command] 
         * This will grab and run the original command sent
         */
        run_command (getenv ("SSH_ORIGINAL_COMMAND"));
    }
    // interactive
    else
    {
        printf ("Interactive sessions are not allowed. Goodbye!\n");
    }

    cleanup ();
    return 0;
}