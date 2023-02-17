#include "smallssh_ssh_auth.h"


int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        fprintf (stderr, "ARGV: Pubkey not provided.\n");
        return 0;
    }

    char* pubkey = calloc (strlen (argv[1]) + 1, sizeof (char));
    strcpy (pubkey, argv[1]);

    MYSQL_RES* res_users = query_pubkey (pubkey);
    free (pubkey);

    char* auth_keys = compare_users (res_users);

    if (auth_keys)
    {
        printf ("%s", auth_keys);
        free (auth_keys);
    }

    mysql_free_result (res_users);
    return 0;
}
