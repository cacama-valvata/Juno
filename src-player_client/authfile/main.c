#include "smallssh_ssh_auth.h"

#define BUFSIZE 256
#define INPUTLEN 32


int main(int argc, char *argv[])
{
    //char pubkey = 'x';

    char pubkey_decoded[1000];
    char query[1000];
    char buf[BUFSIZE];
    char username[INPUTLEN], password[INPUTLEN];

    memset(buf,0,BUFSIZE);
    memset(pubkey_decoded,0,1000);


    strcpy(pubkey_decoded,"AAAAB3NzaC1yc2EAAAADAQABAAABgQDV6pvDAafe6Emu305YWzxuEWgWq6ypPpMftmHVtu5al9+VzLSFFph2J5hqUL06M8W7+5b1a+UXxdns7hUIHYEh2WPxJkPf4xPXyEG3bXeoTXyt4YZ3i+PagmvcYLg4pwUJl2y5A1/ipamdZTqoPNtycIDt62+pPEjBUL7QnE3YPIP6Fzh76SQcPHS46t7MDzSahBkAvaTMErCfYfyFgIrWgcWbVY+pM+JPyfNpAQs/XkYxXtctzieasPqkOlLc/Y2XKeB6SiXZiiOuu8zHTNfuAd1OO1yZ0Bp0+Bph/ZlsLmrPVsEzgw0yzOn+Mz9zMng1flQHQqxA2kLzI8lk8/HbIf9byKzIJebRdsOBJEnY+/xyEO8wxx5bgs3MshtDe9lNyKraaEgS/+c87Q4p1v6tUZdXSRPTSjyeczYxRVAMFU0NVo+WZvnG0KIHx5wMUX46tBiQFlW+gdhs1EC1wdkcC8K9zxZuK9685duhRbZp0DMgWsSC6wJi8mAUhYAT8Es=");

    for (int i = 0; i < argc; i++) {
        printf("Argument %d: %s\n", i, argv[i]);
    }
    
    //grab creds for db query
    if(read_credentials(username, password) == 1)
        return 1;
    
    //append password format
    char* passarg = append_p(password);

    //grab and decode pubkey

    strcat(query,"Use Juno; SELECT count(*) as num_users FROM (SELECT userid from devices where ssh_pubkey = '");
    strcat(query, pubkey_decoded);
    strcat(query, "') as useridlist;");

    
    freopen("/dev/null", "w", stdout);

    execdb(username, passarg, query, buf);

    freopen("/dev/tty", "w", stdout);

    printf("Result: %s\n", buf);

    //parse buf into simple output

    if(strcmp(buf,"1") == 0)
    {
        // send command to login and replace program w/ shell
        printf("command=\"login %s\"",pubkey_decoded);
    }


    else if(strcmp(buf,"0") == 0)
    {
       printf("Error: You are not authorized!\n");
    }
        
        

    else if(strcmp(buf,"0") != 0)
        fprintf(stderr, "Error: should not be > 1\n");



    return 0;
}
