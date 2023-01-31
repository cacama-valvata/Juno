#include "playerclient.h"

// Casey I know this is NOT secure just getting the logic ready :)
int main(int argc, char* argv[])
 {
    char user_input[4096];
    char pubkey[32], privkey[32];
    


    if (argc < 4) 
    {
        printf("Usage: %s [user] [hostname] [shell]\n", argv[0]);
        return 1;
    }

    // check for existing config, if not regen
    if(check_key(pubkey,privkey) == 0)
        wgkeygen(pubkey,privkey);


    
    // very simple menuing 
    while(1)
    {
        printf("\nPlease enter some text: ");
        fgets(user_input, sizeof(user_input), stdin);

        if(strcmp(user_input, "connect\n") == 0 )
            connectclient(argc,argv);
        
        else if(strcmp(user_input, "wgkeygen\n")  == 0 )
            wgkeygen(pubkey, privkey);

        else if(strcmp(user_input, "proccfg\n") == 0 )
            process_config("file.txt", "<your private key here>", privkey);
    
        else if(strcmp(user_input, "stop\n") == 0 )
            break;
        
        else
            printf("UNKNOWN\n");
    }
 

    return 0;
}
