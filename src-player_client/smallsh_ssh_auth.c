#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>


#define BUFSIZE 256


int main(int argc, char *argv[])
{
    //char pubkey = 'x';
    char pubkey_decoded = 'x';
    //char *username;
    char *query;
    //int count;
    // char *ret;
    int send = 0;

    int pipefd[2];
    pid_t pid;
    char buf[BUFSIZE];
    int bytes_read; 

    //grab and decode pubkey

    if (pipe(pipefd) == -1)
    {
        perror("pipe");
        return 1;
    }

    pid = fork();
    if (pid == -1)
    {
        perror("fork");
        return 1;
    }

    if (pid == 0) 
    {  
        // child process
        close(pipefd[0]);  // close unused read end
        dup2(pipefd[1], STDOUT_FILENO);  // redirect stdout to write end of pipe

        // construct SQL query to check for unique user with this public key
        query = "SELECT COUNT(*), username FROM users WHERE pubkey = '";
        query = strcat(query, &pubkey_decoded);
        query = strcat(query, "';");
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

    if(send)
    {

        if (pipe(pipefd) == -1)
        {
            perror("pipe");
            return 1;
        }

        pid = fork();
        if (pid == -1)
        {
            perror("fork");
            return 1;
        }

        if (pid == 0) 
        {  // child process
            close(pipefd[0]);  // close unused read end
            dup2(pipefd[1], STDOUT_FILENO);  // redirect stdout to write end of pipe

            // construct SQL query to check for unique user with this public key
            query = "SELECT, username FROM users WHERE pubkey = '";
            query = strcat(query, &pubkey_decoded);
            query = strcat(query, "';");
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


    return 0;
}
