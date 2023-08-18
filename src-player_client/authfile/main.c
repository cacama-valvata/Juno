#include "smallssh_ssh_auth.h"

#define BUFSIZE 256
#define INPUTLEN 32


int main(int argc, char *argv[])
{
    //char pubkey = 'x';
    char pubkey_decoded[451] = "x";
    char query[1000];
    char buf[BUFSIZE];
    char username[INPUTLEN], password[INPUTLEN];
    
    //grab creds for db query
    if(read_credentials(username, password) == 1)
        return 1;
    
    //append password format
    char* passarg = append_p(password);

    //grab and decode pubkey

    strcat(query,"SELECT COUNT(*), username FROM users WHERE pubkey = '");
    strcat(query, pubkey_decoded);
    strcat(query, "';");

    execdb(username, passarg, query, buf);

    //parse buf into simple output

    if(strcmp(buf,"1") == 0)
    {
        //TO DO: Fix query
        //grab actual username 
        strcat(query,"SELECT ALL, username FROM users WHERE pubkey = '");
        strcat(query, pubkey_decoded);
        strcat(query, "';");

        execdb(username, passarg, query, buf);

        //parse buf into simple output

        // send command to login and replace program w/ shell
        execl("/usr/bin/", "login", buf, "ssh-key", pubkey_decoded,  NULL);
    }
        

    else if(strcmp(buf,"0") != 0)
        fprintf(stderr, "Error: should not be > 1");



    return 0;
}
