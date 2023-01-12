#include <unistd.h>
#include <stdio.h>
#include <string.h>

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



int main() {
    char user_input[4096];
    
    // very simple menuing 
    while(1)
    {
        printf("\nPlease enter some text: ");
        fgets(user_input, sizeof(user_input), stdin);

        if(strcmp(user_input, "heartbeat\n") == 0 )
            heartbeat();
        
        
        else if(strcmp(user_input, "wgupdate\n")  == 0 )
        {
            printf("\nPlease Enter Your key: ");
            fgets(user_input, sizeof(user_input), stdin);
            wgupdate(user_input);
        }
           
        else if(strcmp(user_input, "wgsend\n")  == 0 )
            wgsend();

        else if(strcmp(user_input, "stop\n") == 0 )
            break;

        else
            printf("UNKNOWN\n");
    }
 

    return 0;
}