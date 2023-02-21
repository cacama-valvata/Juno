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

MYSQL_RES* query_db (char* query)
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

char* parse_results (MYSQL_RES* res_users)
{
    int num_users = mysql_num_rows (res_users);

    // catches both 0 keys and >1 keys
    if (num_users != 1)
    {
        fprintf (stderr, "%d keys that match. Authorization failed.\n", num_users);
        return NULL;
    }

    MYSQL_ROW user_info = mysql_fetch_row (res_users);
    // 0: result row

    // safe to assume that this pubkey is indeed the one we're checking?
    char* auth_keys = (char*) calloc (1024, sizeof (char));
    // command="" portion of auth_keys output
    strcpy (auth_keys, user_info[0]);

    return auth_keys;
}


void retrieve_conf(char* key, char* gameid)
{
    char* query = (char*) calloc (1024, sizeof (char));
    MYSQL_RES* res_query;
    char* res;
  

    //query to check if game is ready
    strcat(query,"Use Juno; SELECT ready FROM games WHERE gameid = '");
    strcat(query, gameid);
    strcat(query, "';");
    res_query = query_db(query);
    res = parse_results(res_query);

    if(!res)
        fprintf(stderr,"Error in database, please retry\n");


    //IF GAME READY
    if(strcmp(res,"1") == 0)
    {
        printf("here is your new config %s", key);
    }

        //no game user must wait
    else
        printf("game has not finished initializing");

    return;
}


void heartbeat (char* key, char* userid)
{
    char* query = (char*) calloc (1024, sizeof (char));
    char gameid[BUFSIZE];
    MYSQL_RES* res_query;
    char* res;

    //parse res_users store in BUF

    //search for games w/ user id
    strcat(query,"SELECT gameid FROM game_players WHERE userid = '");
    strcat(query, userid);
    strcat(query, "';");

    res_query = query_db(query);
    int num_games = mysql_num_rows (res_query);

    if(num_games == 0)
    {
        fprintf(stderr,"No games\n");
        return;
    }
   

    MYSQL_ROW gamelist = mysql_fetch_row (res_query);
    //search for and grab the most recent game

    int comp = 0;
    for(int i = 0; i < num_games;i++)
    {
        strcat(query,"SELECT ready FROM games WHERE gameid = '");
        strcat(query, gamelist[i]);
        strcat(query, "';");
        res_query = query_db(query);
        res = parse_results(res_query);

        if(strcmp(res,"1") == 0)
        {
            strcpy(gameid,gamelist[i]);
            comp = 1;
           
            break;
        }

        if(res)
            free(res);

    }
    
    if(comp == 1)
    {
         printf("No games\n");
         return;
    }


    //key is previously used for a  past game
    strcat(query,"SELECT wg_pubkey FROM games WHERE gameid = '");
    strcat(query, gameid);
    strcat(query, "';");
    res_query = query_db(query);
    res = parse_results(res_query);

    if(!res)
    {
        fprintf(stderr,"Error in database, please retry\n");
        return;
    }
    
    if(strcmp(res,key) == 0)
    {
        printf("key already added\n");
        retrieve_conf(key, gameid);
    }

    else if(strcmp(res,key) != 0)
    {
        printf("key updated\n");
        retrieve_conf(key, gameid);
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

void run_command (char* c, char* userid)
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
        heartbeat ("x", userid);
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




