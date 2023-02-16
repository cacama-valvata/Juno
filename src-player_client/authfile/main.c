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
    //FILE *log_file;

    memset(query,0,BUFSIZE);
    memset(buf,0,BUFSIZE);
    memset(pubkey_decoded,0,1000);


    strcpy(pubkey_decoded,"AAAAB3NzaC1yc2EAAAADAQABAAABgQCT5h3mgwZQkogttDoixTYtk5KHumbCs3BXAp2c27VYZhjPOSdDR5GYWGm0U+w6TnHein74XSEIPozypSP7yfOJK8Cr1tsuR1ptJfOX6c0bg1eNbiiNVwP6d5Zz6suiDK6KI03x4DJkTE/doaA9g/2LuiZIYNoXk9diPMwxB+lJdVLPFBaxcTJg9Pu/nT1sq72rhBEbR6wAClnqqRjQI7U/vr+0EGqwXHo+ocXhBunThgzCgLR5QzOIPJqNO7HBoOyrfu/wco+SrYnckT2hiQDvTLMQ95jmRLKMa+I7VQavG6yku09F3C23cEa4KpGXZ+9Z9HUYuVZK3isS3S7oLMLCpVIm9qpnhqcjp6frgt3SXGTsFexvFB7rJyoBH7Nuio25ow16pfcPSbdqGI7dy2+Anf15+/p6GY3/QkaAwIfJl+eEpbPk587M7FNpYNNvBW1BMgtySW+Vc74zg7FoF19vZEuP3BJqgrNtr3CTakdLwx0X6d7iwh698xypsKKG6jE=");

    
    //grab creds for db query
    if(read_credentials(username, password) == 1)
        return 1;
    
    //append password format
    char* passarg = append_p(password);

    //grab and decode pubkey

    strcat(query,"Use Juno; SELECT count(*) as num_users FROM (SELECT userid from devices where ssh_pubkey = '");
    strcat(query, pubkey_decoded);
    strcat(query, "') as useridlist;");

    execdb(username, passarg, query, buf);

    //fprintf(stderr, "%s\n", buf);

    //parse buf into simple output

    // log_file = fopen("logfile.txt", "a");

    //fprintf(log_file,"Buf output: %s\n",buf);

    if(strcmp(buf,"1") == 0)
    {
        // send command to login and replace program w/ shell
        //fprintf(stderr, "command=\"login appusername\" ssh-rsa %s user@hostname\n",pubkey_decoded);
        printf("command=\"login appusername\" ssh-rsa %s guest@ip-172-31-5-54\n",pubkey_decoded);
    }


    else if(strcmp(buf,"0") == 0)
    {
       fprintf(stderr,"Error: You are not authorized!\n");
    }
        
        

    else if(strcmp(buf,"0") != 0)
        fprintf(stderr, "Error: should not be > 1\n");


    //fclose(log_file);

    return 0;
}
