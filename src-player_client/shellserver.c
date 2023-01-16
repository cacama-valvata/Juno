#include <unistd.h>
#include <stdio.h>
#include <string.h>

char* login_user = NULL;


void login (char* username)
{
    if (!login_user)
        login_user = username;
}

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

void menu (char* user_input)
{
    if(strcmp(user_input, "heartbeat\n") == 0 )
            heartbeat();
        else if(strcmp(user_input, "wgupdate\n")  == 0 )
        {
            printf("\nPlease Enter Your key: ");
            fgets(user_input, sizeof(user_input), stdin);
            wgupdate(user_input);
        }
        else if (! strcmp (user_input, "login\n"))
        {
            char username [256];
            printf("Username: ");
            fgets(username, sizeof(username), stdin);
            login (username);
            printf("%s\n", login_user);
        }
        else if(strcmp(user_input, "wgsend\n")  == 0 )
            wgsend();
        //else if(strcmp(user_input, "stop\n") == 0 )
        //    break;
        else
            printf("UNKNOWN\n");
}

int main(int argc, char* argv[]) {
    
    //char* command = NULL;

    if (argc > 2)
    {
        if (! strcmp (argv[1], "-c"))
        {
            menu (argv[2]);
            return 0;
        }
    }
    
    char user_input[4096];

    // very simple menuing 
    while(1)
    {
        printf("\nPlease enter some text: ");
        fgets(user_input, sizeof(user_input), stdin);

        menu (user_input);
    }


    return 0;
}