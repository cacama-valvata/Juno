#include "playerclient.h"

#define BUFSIZE 256
// Casey I know this is NOT secure just getting the logic ready :)
int main(int argc, char* argv[])
 {
    char pubkey[32], privkey[32];
    char buf[BUFSIZE];

    // check for existing config, if not regen
    if(check_key(pubkey,privkey) == 0)
        wgkeygen(pubkey,privkey);

    // very simple menuing 
    while(1)
    {
        char **words = NULL;
        int num_words = get_words(&words);

        if(strcmp(words[0], "connect") == 0 )
        {
            //void connectclient(char* pubkey, char* user, char* host, char* command, char* hkeys, char* buf)
            if(num_words < 4)
                printf("Error! Usage:\n");

            else
                connectclient(words[1],words[2],words[3],words[4],pubkey,buf);
        }
            
        
        else if(strcmp(words[0], "wgkeygen")  == 0 )
        {
            wgkeygen(pubkey, privkey);
        }
            

        else if(strcmp(words[0], "proccfg") == 0 )
        {
            process_config("file.txt", "<your private key here>", privkey);
        }
            
    
        else if(strcmp(words[0], "stop") == 0 )
        {
            for (int i = 0; i < num_words; i++)
            {
                free(words[i]);
            }
            free(words);
            break;
        }
        
        else
            printf("UNKNOWN\n");


        for (int i = 0; i < num_words; i++)
        {
            free(words[i]);
        }
        free(words);
    }
 

    return 0;
}
