#include "authlookup.h"

char* sanitize_string(char* input_string) {
  char* sanitized_string = (char*) malloc(MAX_STRING_LENGTH * sizeof(char));
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


int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        fprintf (stderr, "ARGV: Pubkey not provided.\n");
        return 0;
    }

    char* input_string = argv[1];
    char* sanitized_string = sanitize_string(input_string);

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
