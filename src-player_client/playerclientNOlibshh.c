#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include "wireguard.h"

#define BUF_SIZE 256

//init the connection and allow user to mess around in shell
void connectclient(int argc, char *argv[])
{
    if (argc < 4) 
    {
        printf("Usage: %s [user] [hostname] [shell]\n", argv[0]);
        return;
    }

    int pipefd[2];
    pid_t pid;
    char buf[BUF_SIZE];

    if (pipe(pipefd) == -1)
    {
        perror("pipe");
        return;
    }

    pid = fork();
    if (pid == -1)
    {
        perror("fork");
        return;
    }

    if (pid == 0) 
    {  // child process
        close(pipefd[0]);  // close unused read end
        dup2(pipefd[1], STDOUT_FILENO);  // redirect stdout to write end of pipe
        char *args[] = {"ssh", argv[1], "@", argv[2], argv[3], NULL};
        execvp("ssh", args);
        return;
    } 

    else 
    {  // parent process
        close(pipefd[1]);  // close unused write end
        while (read(pipefd[0], buf, BUF_SIZE) > 0)
        {
            printf("%s", buf); 
            //do stuff with the read memory
            memset(buf, 0, BUF_SIZE);
           
        }
    }

    return;
}

void wgkeygen(){


  // generate public key (if not already existing)

  // Generate a WireGuard public key
  wg_key privkey;
  wg_generate_private_key(privkey);

  wg_key_b64_string pubkeys;
  wg_key_to_base64(pubkeys, privkey);

  //generate and maybe send to file
  printf("here is my public key %s\n", pubkeys);

  return;

}



int main(int argc, char* argv[])
 {
    char user_input[4096];
    
    // very simple menuing 
    while(1)
    {
        printf("\nPlease enter some text: ");
        fgets(user_input, sizeof(user_input), stdin);

        if(strcmp(user_input, "connect\n") == 0 )
            connectclient(argc,argv);
        
        
        else if(strcmp(user_input, "wgkeygen\n")  == 0 )
            wgkeygen();

        else if(strcmp(user_input, "stop\n") == 0 )
            break;

        else
            printf("UNKNOWN\n");
    }
 

    return 0;
}
