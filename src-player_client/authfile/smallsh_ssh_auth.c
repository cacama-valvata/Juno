#include "smallssh_ssh_auth.h"

#define BUFSIZE 256
#define INPUTLEN 32


void read_credentials(char *username, char *password)
{
    FILE *file;
    file = fopen("credentials.txt", "r");
    if (file == NULL) {
        printf("Error opening file");
        return;
    }
    fgets(username, INPUTLEN, file);
    fgets(password, INPUTLEN, file);
    fclose(file);
}

void execdb(char *username, char *password, char* query, char* buf)
{

    int pipefd[2];
    pid_t pid;
    int bytes_read; 



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
    {  
        // child process
        close(pipefd[0]);  // close unused read end
        dup2(pipefd[1], STDOUT_FILENO);  // redirect stdout to write end of pipe

        // construct SQL query to check for unique user with this public key

        execl("/usr/bin/mysql", "mysql", "-u", "user", "-p", "password", "-e", query, NULL);
    } 

    else 
    {  
        // parent process
        close(pipefd[1]);
        bytes_read = read(pipefd[0], buf, BUFSIZE);
        if (bytes_read > 0) 
        {
            buf[bytes_read] = '\0';
            printf("%s", buf);
        }
        close(pipefd[0]);
        wait(NULL);
    }
}
