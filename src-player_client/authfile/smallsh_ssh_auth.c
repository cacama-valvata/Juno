#include "smallssh_ssh_auth.h"

#define BUFSIZE 256
#define INPUTLEN 100


char *append_p(const char *str) {
    size_t len = strlen(str);
    char *result = malloc(len + 3);
    
    strcpy(result, "-p");
    strcat(result, str);
    return result;
}


int read_credentials(char *username, char *password)
{
    //memset(username,0,INPUTLEN);
    FILE *file;
    file = fopen("credentials.txt", "r");
    if (file == NULL) {
        printf("Error opening file\n");
        return 1;
    }
    fgets(username, INPUTLEN, file);
    fgets(password, INPUTLEN, file);

    username[strcspn(username, "\n")] = 0;
    password[strcspn(password, "\n")] = 0;

    int len = strlen(username);
    username[len - 1] = '\0';

    fclose(file);
    
    return 0;
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
        freopen("/dev/null", "w", stderr);

        execl("/usr/bin/sudo", "sudo", "/usr/bin/mysql", "mysql", "-u", username, password, "-e", query, (char *) NULL);
    } 

    else 
    {
        close(pipefd[1]);  // close unused write end
        char *token; 
        while (read(pipefd[0], buf, BUFSIZE) > 0)
        {

            printf("%s", buf); 
            //do stuff with the read memory
            token = strtok(buf, "\n");
            while(1) 
            {
                //printf( " %s\n", token );
                strcpy(buf,token);

                token = strtok(NULL, "\n");
                if(token == NULL)
                    break;
            }

        }
        /*
        // parent process
        close(pipefd[1]);
        wait(NULL);
        bytes_read = read(pipefd[0], buf, BUFSIZE);
        buf[bytes_read] = '\0';

        char *line = strtok(buf, "\n");
        while (line != NULL) {
            if (strncmp(line, "|", 1) == 0) {
                char *column = strtok(line, "|");
                int i = 0;
                while (column != NULL) 
                {
                    if (i == 1) 
                    {
                        //Do SOMETHING  with the info, for now print
                        printf("%s\n", column);
                    }
                    i++;
                    column = strtok(NULL, "|");
                }
            }
            line = strtok(NULL, "\n");
        }
        close(pipefd[0]);

        */
    }
}
