#include "shellserver.h"


#define BUFSIZE 256
#define INPUTLEN 32



int read_credentials (char* username, char* password, char* host, char* credfile)
{
    FILE *file = fopen (credfile, "r");
    if (file == NULL) {
        return 1;
    }

    fgets(username, INPUTLEN, file);
    fgets(password, INPUTLEN, file);
    fgets(host, INPUTLEN, file);

    username[strcspn(username, "\n")] = 0;
    password[strcspn(password, "\n")] = 0;
    host[strcspn(host, "\n")] = 0;

    fclose(file);
    
    return 0;
}

MYSQL_RES* query_pubkey (char* query)
{
    MYSQL* con = mysql_init (NULL);
    if (! con)
    {
        fprintf (stderr, "Error initializing MySQL connection.\n");
        exit (255);
    }

    char* username = calloc (INPUTLEN, sizeof (char));
    char* password = calloc (INPUTLEN, sizeof (char));
    char* host = calloc (INPUTLEN, sizeof (char));

    int read_err = read_credentials (username, password, host, "/opt/Juno/credentials.txt");
    if (read_err)
    {
        fprintf (stderr, "Error reading credentials from file.\n");
        mysql_close (con);
        exit (255);
    }

    MYSQL* err = mysql_real_connect (con, host, username, password, "Juno", 0, NULL, 0);

    free (username);
    free (password);
    free (host);

    if (! err)
    {
        fprintf (stderr, "Error opening connection to MySQL server.\n");
        mysql_close (con);
        exit (255);
    }

    if (mysql_query (con, query))
    {
        free (query);
        fprintf (stderr, "Error executing query in database.\n");
        mysql_close (con);
        exit (255);
    }

    free (query);

    MYSQL_RES* res_users = mysql_store_result (con);
    if (! res_users)
    {
        fprintf (stderr, "Error retrieving result set.\n");
        mysql_close (con);
        exit (255);
    }

    mysql_close (con);
    return res_users;
}

void retrieve_conf(char* key, char* gameid)
{
    char query[1000];
    char buf[BUFSIZE];
    MYSQL_RES* res_users;

    memset(query,0,1000);

    //query to check if game is ready
    strcat(query,"Use Juno; SELECT username FROM users WHERE userid = '");
    strcat(query, gameid);
    strcat(query, "';");
    res_users = query_pubkey(query);

    //parse res_users

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


void heartbeat (char* key)
{
    char query[1000];
    //char buf[BUFSIZE];
    char userid[BUFSIZE];
    char gameid[BUFSIZE];
    MYSQL_RES* res_users;


    memset(query,0,1000);

    //TO DO: Fix query
    //grab user id to search for games
    strcat(query,"Use Juno; SELECT username FROM users WHERE userid = '");
    strcat(query, key);
    strcat(query, "';");
    res_users = query_pubkey(query);

    //parse res_users store in BUF

    //TO DO: Fix query
    //search for games w/ user id
    strcat(query,"Use Juno; SELECT username FROM users WHERE userid = '");
    strcat(query, buf);
    strcat(query, "';");
    res_users = query_pubkey(query);

    //parse res_users


    //parse res_users store in BUF
    //save for later
    strcpy(gameid, buf);
    
    // If res_users empty
    if(buf == NULL)
    {
        printf("NO GAMES");
        return;
    }


    //TO DO: Fix query
    //figure out if game is in the present or past
    strcat(query,"Use Juno; SELECT username FROM users WHERE userid = '");
    strcat(query, buf);
    strcat(query, "';");
    res_users = query_pubkey(query);

    //parse res_users store in BUF


    //parse buf into simple output

    // IF GAME IS IN THE PAST > MAKE A NEW CONFIG (SOME EXEC MAGIC)
    if(buf == NULL)
    {
        printf("make a new public key");
        return;
    }

    //TO DO: Fix query
    //VERIFY USER KEY MATCHES ON FILE
    strcat(query,"Use Juno; SELECT username FROM users WHERE userid = '");
    strcat(query, buf);
    strcat(query, "';");
    res_users = query_pubkey(query);

    //parse res_users store in BUF


    // IF not equal to key in wg config, update the key
    if(strcmp(buf,key) != 0)
    {
        strcat(query,"Use Juno; SELECT username FROM users WHERE userid = '");
        strcat(query, buf);
        strcat(query, "';");
        res_users = query_pubkey(query);

         //parse res_users store in BUF


        printf("key updated\n");
        retrieve_conf(key, gameid);
        return;
    }

    //if key is equal generate that sweet sweet config
    else
    {
        printf("key already added!\n");
        retrieve_conf(key, gameid);
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
        heartbeat ("x");
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
    else if (! strcmp(arg, "ping")) 
    {
        printf("shell responds with PONG!");
    }
    else
    {
        printf ("Unknown command.\n");
    }

    // cleanup 
    free (command);
    return;
}




