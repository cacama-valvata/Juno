#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* 
 * Usernames can only be composed of
 * - lowercase alphabet
 * - numerics
 * - underscore
 */
const char * const allowed_chars = "abcdefghijklmnopqrstuvwxyz0123456789_";

/* 
 * Records current user that we are running commands for
 * Authenticated by SSH server
 */
char* session_user = NULL;


void heartbeat ()
{
    // poke arians db to ensure its still alive
    printf ("here is your heartbeat :D\n");
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

    // each function should check that were logged in!
    
    // copy the argument for tok'ing
    char* command = (char*) calloc (4096, sizeof (char));
    memcpy (command, c, strlen (c));
    // tokenize for (command, arg)
    char* arg = strtok (command, " ");

    if (! strcmp (arg, "heartbeat"))
    {
        heartbeat ();
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

int login (char* c)
{
    // copy the argument for tok'ing
    char* command = (char*) calloc (4096, sizeof (char));
    memcpy (command, c, strlen (c));
    // tokenize for (command, arg)
    char* arg = strtok (command, " ");

    // check that the first command is indeed 'login'
    // as it should be
    if (strcmp (arg, "login"))
    {
        free (command);
        return 1;
    }

    // grab the argument
    arg = strtok (NULL, " ");

    // if there is no arg (no username to set), then fail
    if (! arg)
    {
        free (command);
        return 1;
    }

    // check that the requested username is made up of only allowed characters
    if (strspn (arg, allowed_chars) < strlen (arg))
    {
        free (command);
        return 1;
    }

    // copy username into session_user
    session_user = (char*) calloc (strlen (arg) + 1, sizeof (char));
    memcpy (session_user, arg, strlen (arg));

    // cleanup
    free (command);
    return 0;
}

void cleanup ()
{
    if (session_user)
        free (session_user);
}

int main (int argc, char* argv[]) 
{
    /*
     * If the ssh server and authentication are
     * set up correctly, the shell should always
     * be called non-interactively, and should
     * run the login command before anything else
     */

    // non-interactive commands
    if (argc > 2 && ! strcmp (argv[1], "-c"))
    {
        /* 
         * login() will check that our command is indeed 'login'
         * returns 0 on success
         */
        int r = login (argv[2]);
        // if we failed to login, cleanup and return
        if (r)
        {
            printf ("Authentication failed.");
            cleanup ();
            return 1;
        }
        printf ("Hello, %s.\n", session_user);

        /* 
         * Client would run: ssh host [command] 
         * This will grab and run the original command sent
         */
        run_command (getenv ("SSH_ORIGINAL_COMMAND"));
    }
    // interactive
    else
    {
        printf ("Interactive sessions are not allowed. Goodbye!\n");
    }

    cleanup ();
    return 0;
}