#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

const char * const allowed_chars = "abcdefghijklmnopqrstuvwxyz0123456789_";

char* session_user = NULL;


void heartbeat()
{

  // poke arians db to ensure its still alive
  printf("here is your heartbeat :D\n");
  return;

}


void wgupdate(char* key)
{

    //sending pub key for config
    printf("here is my public key %s\n",key);

    char wg_config[4096];

    //use exec to scp generated file
    //print config to standard out
    printf("here is your config: %s\n", wg_config);

  return;
}


void wgsend()
{
    char user_input[100];
    char concatenated_string[1000] = {0};

    // 'read' file line by line from standard in
    while(1)
    {
        printf("Enter some text or type stop to end: ");
        fgets(user_input, sizeof(user_input), stdin);

        if (strcmp(user_input, "stop\n") == 0)
            break;

        strcat(concatenated_string, user_input);
    }

    // reconstruct and send to server
    printf("completed file: %s", concatenated_string);
}

void menu (char* user_input)
{
        if(strcmp(user_input, "heartbeat\n") == 0 )
            heartbeat();
        else if(strcmp(user_input, "wgupdate\n")  == 0 )
        {
            printf("\nPlease Enter Your key: ");
            fgets(user_input, sizeof(user_input), stdin);
            wgupdate(user_input);
        }
        else if(strcmp(user_input, "wgsend\n")  == 0 )
            wgsend();
        //else if(strcmp(user_input, "stop\n") == 0 )
        //    break;
        else
            printf("UNKNOWN\n");
}

int login (char* c)
{
    char* command = (char*) calloc (4096, sizeof (char));
    memcpy (command, c, strlen(c));
    char* arg = strtok (command, " ");

    if (strcmp (arg, "login"))
        return 1;

    arg = strtok (NULL, " ");

    if (! arg)
        return 1;

    if (strspn (arg, allowed_chars) < strlen (arg))
        return 1;

    session_user = (char*) calloc (strlen (arg) + 1, sizeof (char));
    memcpy (session_user, arg, strlen (arg));

    // free

    return 0;
}

int main(int argc, char* argv[]) {
    
    char* command = (char*) calloc (4096, sizeof (char));

    // non-interactive
    if (argc > 2 && !strcmp (argv[1], "-c"))
    {
        login (argv[2]);
        printf ("Hello, %s.\n", session_user);

        // SSH_ORIGINAL_COMMAND
    }

    while(1)
    {
        memset (command, '\0', 4096);
        printf("\nPlease enter some text: ");
        fgets(command, 4095, stdin);
        printf("%s", command);
        menu (command);
    }

    // interactive
    /*else
    {
        while(1)
        {
            printf("\nPlease enter some text: ");
            fgets(command, sizeof(command), stdin);

            menu (command);
        }
    }*/

    // cleanup
    free (command);
    if (session_user)
        free (session_user);

    return 0;
}