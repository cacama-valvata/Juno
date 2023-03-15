#include "authlookup.h"

#define INPUTLEN 1024


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

MYSQL_RES* query_pubkey (char* pubkey)
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

    char* query = (char*) calloc (1024, sizeof (char));
    strcpy (query, "SELECT ssh_prefix, ssh_pubkey, ssh_suffix, user_id, id FROM account_userdevice where ssh_pubkey = \"");
    strcat (query, pubkey);
    strcat (query, "\";");

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

char* compare_users (MYSQL_RES* res_users)
{
    int num_users = mysql_num_rows (res_users);

    // catches both 0 keys and >1 keys
    if (num_users != 1)
    {
        fprintf (stderr, "%d keys that match. Authorization failed.\n", num_users);
        return NULL;
    }

    MYSQL_ROW user_info = mysql_fetch_row (res_users);
    // 0: ssh_prefix, 1: ssh_pubkey, 2: ssh_suffix, 3: userid

    // safe to assume that this pubkey is indeed the one we're checking?
    char* auth_keys = (char*) calloc (1024, sizeof (char));
    // command="" portion of auth_keys output
    strcpy (auth_keys, "command=\"login ");
    strcat (auth_keys, user_info[3]);
    // the device ID
    strcat (auth_keys, " ");
    strcat (auth_keys, user_info[4]);
    strcat (auth_keys, "\" ");
    
    // the key itself, rebuilt
    strcat (auth_keys, user_info[0]);
    strcat (auth_keys, " ");
    strcat (auth_keys, user_info[1]);
    strcat (auth_keys, " ");
    strcat (auth_keys, user_info[2]);



    return auth_keys;
}
