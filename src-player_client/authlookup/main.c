#include "authlookup.h"



int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        fprintf (stderr, "ARGV: Pubkey not provided.\n");
        return 0;
    }

    char* input_string = argv[1];
    char* sanitized_string = sanitize_string(input_string);

    //printf("KEY: %s", sanitized_string);

    char* pubkey = calloc (strlen (sanitized_string) + 1, sizeof (char));
    strcpy (pubkey, sanitized_string);

    MYSQL_RES* res_users = query_pubkey (pubkey);
    free (pubkey);

    char* auth_keys = compare_users (res_users);

    if (auth_keys)
    {
        printf ("%s\n", auth_keys);
        free (auth_keys);
    }

    mysql_free_result (res_users);
    return 0;
}
