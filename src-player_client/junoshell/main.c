#include "junoshell.h"

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
void cleanup ();

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


int main (int argc, char* argv[]) 
{
    /*
     * If the ssh server and authentication are
     * set up correctly, the shell should always
     * be called non-interactively, and should
     * run the login command before anything else
     */

    
    for (int i = 0; i < argc; i++) {
        printf("[1]Argumentz %d: %s\n", i, argv[i]);
    }

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
        run_command (getenv ("SSH_ORIGINAL_COMMAND"), session_user);
    }
    // interactive
    else
    {
        printf ("Interactive sessions are not allowed. Goodbye!\n");
    }

    cleanup ();
    return 0;
}


void cleanup ()
{
    if (session_user)
        free (session_user);
}