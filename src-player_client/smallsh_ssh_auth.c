#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
 {
    char pubkey, pubkey_decoded;
    char *username;
    char *query;
    int count;
    char *ret;
    bool send = 0;

    int pipefd[2];
    pid_t pid;
    char buf[BUF_SIZE];

    //grab and decode pubkey

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

        // construct SQL query to check for unique user with this public key
        query = "SELECT COUNT(*), username FROM users WHERE pubkey = '";
        query = strcat(query, pubkey_decoded);
        query = strcat(query, "';");
        execl("/usr/bin/mysql", "mysql", "-u", "user", "-p", "password", "-e", query, NULL);
        
        if(count == 0)
            print("NONE");

        else if(count == 1)
        {
            print("ONE");
        }
        
        else
            print("PANIC");

        return;
    } 

    else 
    {  // parent process
        close(pipefd[1]);  // close unused write end
        while (read(pipefd[0], buf, BUF_SIZE) > 0)
        {

            if(strstr(buf, "ONE"))
                send = 1;
            
            else if(strstr(buf, "PANIC"))
                print("Server: TOO MANY USERS");

            memset(buf, 0, BUF_SIZE);
           
        }
    }

    if(send)
    {

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

            // construct SQL query to check for unique user with this public key
            query = "SELECT, username FROM users WHERE pubkey = '";
            query = strcat(query, pubkey_decoded);
            query = strcat(query, "';");
            execl("/usr/bin/mysql", "mysql", "-u", "user", "-p", "password", "-e", query, NULL);
            
            return;
        } 

        else 
        {  // parent process
            close(pipefd[1]);  // close unused write end
            while (read(pipefd[0], buf, BUF_SIZE) > 0)
            {
                // grab and exec to login from shell with username
                memset(buf, 0, BUF_SIZE);
            
            }
        }
    }


    return 0;
}
