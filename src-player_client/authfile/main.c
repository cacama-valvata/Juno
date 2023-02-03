#include "smallssh_ssh_auth.h"

#define BUFSIZE 256
#define INPUTLEN 32


int main(int argc, char *argv[])
{
    //char pubkey = 'x';
    char pubkey_decoded = 'x';
    char *query;
    char buf[BUFSIZE];
    char username[INPUTLEN], password[INPUTLEN];
    
    //grab creds for db query
    read_credentials(username, password);

    //grab and decode pubkey

    query = "SELECT COUNT(*), username FROM users WHERE pubkey = '";
    query = strcat(query, &pubkey_decoded);
    query = strcat(query, "';");

    execdb(username, password, query, buf);

    //parse buf into simple output

    if(strcmp(buf,"1") == 0)
    {
        //TO DO: Fix query
        //grab actual username 
        query = "SELECT ALL, username FROM users WHERE pubkey = '";
        query = strcat(query, &pubkey_decoded);
        query = strcat(query, "';");

        execdb(username, password, query, buf);

        //parse buf into simple output

        // send command to login and replace program w/ shell
        execl("/usr/bin/", "login", buf, "ssh-key", &pubkey_decoded,  NULL);
    }
        

    else if(strcmp(buf,"0") != 0)
        fprintf(stderr, "Error: should not be > 1");



    return 0;
}
