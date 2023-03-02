#include "junoshell.h"


#define BUFSIZE 256
#define INPUTLEN 32

char* sanitize_string(char* input_string) {
  char* sanitized_string = (char*) malloc(1000 * sizeof(char));
  int i, j;
  for (i = 0, j = 0; i < strlen(input_string); i++) {
    switch (input_string[i]) {
      case ';':
        sanitized_string[j++] = '\\';
        sanitized_string[j++] = ';';
        break;
      case '-':
        sanitized_string[j++] = '\\';
        sanitized_string[j++] = '-';
        break;
      case '*':
        sanitized_string[j++] = '\\';
        sanitized_string[j++] = '*';
        break;
      case '"':
        sanitized_string[j++] = '\\';
        sanitized_string[j++] = '"';
        break;
      case '\\':
        sanitized_string[j++] = '\\';
        sanitized_string[j++] = '\\';
        break;
      default:
        sanitized_string[j++] = input_string[i];
        break;
    }
  }
  sanitized_string[j] = '\0';
  return sanitized_string;
}



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

    int read_err = read_credentials (username, password, host, "/opt/Juno/mysql.creds");
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
    strcat(query,"Use Juno; SELECT ready FROM games_game WHERE id = '");
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


void heartbeat (char* key, char* userid, char* deviceid)
{
    char* query = (char*) calloc (1024, sizeof (char));
    char gameid[BUFSIZE];
    MYSQL_RES* res_query;
    char* res;

    strcat(query,"SELECT device_id FROM games_gameplayer WHERE user_id = '");
    strcat(query, userid);
    strcat(query, "';");
    res_query = query_db(query);
    res = parse_results(res_query);

    if(strcmp(res,deviceid) != 0)
    {
        printf("Error! Authing from wrong device")
    }

  

    //search for games w/ user id
    strcat(query,"SELECT game_id FROM games_gameplayer WHERE user_id = '");
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

    //iterate through all games (maybe check time stamp, returns ready game)
    int comp = 0;
    for(int i = 0; i < num_games;i++)
    {
        strcat(query,"SELECT ready FROM games_game WHERE id = '");
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
    
    if(comp == 0)
    {
         printf("No present games\n");
         return;
    }


    //key is previously used for a  past game
    strcat(query,"SELECT wg_pubkey FROM games_gameplayer WHERE gameid = '");
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


void run_command (char* c, char* userid, char* deviceid)
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

        char* input_string = arg;
        char* sanitized_string = sanitize_string(input_string);
        heartbeat (sanitized_string, userid, deviceid);
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




