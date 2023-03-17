#include "playerclient.h"

#define BUFSIZE 256
int main(int argc, char* argv[])
 {
    char pubkey[1024], privkey[1024];
    memset(pubkey, 0, 1024);
    //char buf[BUFSIZE];

    // check for existing config, if not regen
    if(check_key(pubkey,privkey) == 0)
        wgkeygen(pubkey,privkey);

    // very simple menuing 
    while(1)
    {
        char **words = NULL;
        char* cfg;
        int num_words = get_words(&words);

        if(strcmp(words[0], "connect") == 0 )
        {

            if(num_words < 5)
                printf("Usage: connect [hostname] [username] [key path] [command]\n");


            else
            {
                char *output = ssh_exec(words[1],words[2],words[3],words[4],pubkey);
             
                //HERE indicates that output contains VALID WG config
                if(strstr(output,"[Interface]") != NULL)
                {
                    FILE *fp = fopen("config.txt","w");

                    if(fp == NULL)
                    {
                        perror("Failed to open output file");
                        exit(1);
                    }
                    cfg = strchr(output,'.');
                    *cfg = '\0';

                    fprintf(fp,"%s\n",cfg+2);
                    fclose(fp);
                    printf("Config written to file\n");
                    
                    process_config("config.txt", "<your private key here>", privkey);
                }

                else
                    printf("%s\n",output);
                    
                free(output);
            }
                
        }
            
        else if(strcmp(words[0], "wgkeygen")  == 0 )
        {
            wgkeygen(pubkey, privkey);
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
