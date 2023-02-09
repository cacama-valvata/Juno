#include "shellserver.h"


#define BUFSIZE 256
#define INPUTLEN 32



int read_credentials(char *username, char *password)
{
    //memset(username,0,INPUTLEN);
    FILE *file;
    file = fopen("credentials.txt", "r");
    if (file == NULL) {
        printf("Error opening file\n");
        return 1;
    }
    fgets(username, INPUTLEN, file);
    fgets(password, INPUTLEN, file);

    username[strcspn(username, "\n")] = 0;
    password[strcspn(password, "\n")] = 0;

    int len = strlen(username);
    username[len - 1] = '\0';

    fclose(file);
    
    return 0;
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
        freopen("/dev/null", "w", stderr);

        execl("/usr/bin/sudo", "sudo", "/usr/bin/mysql", "mysql", "-u", username, password, "-e", query, (char *) NULL);
    } 

    else 
    {
        close(pipefd[1]);  // close unused write end
        char *token; 
        while (read(pipefd[0], buf, BUFSIZE) > 0)
        {

            printf("%s", buf); 
            //do stuff with the read memory
            token = strtok(buf, "\n");
            while(1) 
            {
                //printf( " %s\n", token );
                strcpy(buf,token);

                token = strtok(NULL, "\n");
                if(token == NULL)
                    break;
            }

        }
        /*
        // parent process
        close(pipefd[1]);
        wait(NULL);
        bytes_read = read(pipefd[0], buf, BUFSIZE);
        buf[bytes_read] = '\0';

        char *line = strtok(buf, "\n");
        while (line != NULL) {
            if (strncmp(line, "|", 1) == 0) {
                char *column = strtok(line, "|");
                int i = 0;
                while (column != NULL) 
                {
                    if (i == 1) 
                    {
                        //Do SOMETHING  with the info, for now print
                        printf("%s\n", column);
                    }
                    i++;
                    column = strtok(NULL, "|");
                }
            }
            line = strtok(NULL, "\n");
        }
        close(pipefd[0]);

        */
    }
}

void retrieve_conf(char* key, char* username, char* password, char* gameid)
{
    char query[1000];
    char buf[BUFSIZE];

    memset(query,0,1000);

    strcat(query,"SELECT, ready FROM games, where gameid = '");
    strcat(query, gameid);
    strcat(query, "';");
    execdb(username,password,query, buf);

    //pase buf into simple output

    //IF GAME READY
    if(strcmp(buf,"1") == 0)
    {
        // TODO: How to generate WG config
        printf("here is your new config %s", key);
    }

        //no game user must wait
    else
        printf("game has not finished initializing");

    return;
}

char *append_p(const char *str) {
    size_t len = strlen(str);
    char *result = malloc(len + 3);
    
    strcpy(result, "-p");
    strcat(result, str);
    return result;
}



void heartbeat (char* key, char* username, char* password)
{
    char *query;
    char buf[BUFSIZE];
    char userid[BUFSIZE];
    char gameid[BUFSIZE];
    char* passarg = append_p(password);

    //TO DO: Fix query
    //grab user id to search for games
    query = "SELECT, user_id FROM devices, where pubkey = '";
    query = strcat(query, key);
    query = strcat(query, "';");
    execdb(username,passarg,query, buf);

    //parse buf into simple output
    strcpy(userid, buf);

    //TO DO: Fix query
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


    //TO DO: Fix query
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

    //TO DO: Fix query
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

    free(passarg);
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




