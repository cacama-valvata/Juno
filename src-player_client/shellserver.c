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

void run_command (char* c)
{
    if (! c)
        return;
    
    char* command = (char*) calloc (4096, sizeof (char));
    memcpy (command, c, strlen (c));
    char* arg = strtok (command, " ");

    if(strcmp(arg, "heartbeat") == 0 )
    {
        heartbeat();
    }
    else if(strcmp(arg, "wgupdate")  == 0 )
    {
        //printf("\nPlease Enter Your key: ");
        //fgets(c, sizeof(c), stdin);
        arg = strtok (NULL, " ");
        if (! arg)
            return;
        wgupdate(arg);
    }
    else if(strcmp(arg, "wgsend")  == 0 )
    {
        wgsend();
    }
    else
    {
        printf("Unknown command.\n");
    }
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

    free (command);

    return 0;
}

int main(int argc, char* argv[]) {

    // non-interactive commands
    if (argc > 2 && !strcmp (argv[1], "-c"))
    {
        int r = login (argv[2]);
        if (r)
            // free session_user
            return 1;
        printf ("Hello, %s.\n", session_user);

        // SSH_ORIGINAL_COMMAND
        run_command (getenv ("SSH_ORIGINAL_COMMAND"));
    }
    // interactive
    else
        printf ("Interactive sessions are not allowed. Goodbye!\n");

    // cleanup
    if (session_user)
        free (session_user);

    return 0;
}