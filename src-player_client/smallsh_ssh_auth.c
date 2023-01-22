#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>


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


int main(int argc, char *argv[])
{
    //char pubkey = 'x';
    char pubkey_decoded = 'x';
    char *query;
    char buf[BUFSIZE];
    char username[INPUTLEN], password[INPUTLEN];
    
    //grab creds for db query
    read_credentials(username, password);

    //grab and decode pubkey

    query = "SELECT COUNT(*), username FROM users WHERE pubkey = '";
    query = strcat(query, &pubkey_decoded);
    query = strcat(query, "';");

    execdb(username, password, query, buf);

    //parse buf into simple output

    if(strcmp(buf,"1") == 0)
    {
        //grab actual username 
        query = "SELECT ALL, username FROM users WHERE pubkey = '";
        query = strcat(query, &pubkey_decoded);
        query = strcat(query, "';");

        execdb(username, password, query, buf);

        //parse buf into simple output

        // send command to login and replace program w/ shell
        execl("/usr/bin/", "login", buf, "ssh-key", &pubkey_decoded,  NULL);
    }
        

    else if(strcmp(buf,"0") != 0)
        fprintf(stderr, "Error: should not be > 1");



    return 0;
}
