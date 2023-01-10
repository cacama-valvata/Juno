#include <unistd.h>
#include <stdio.h>
#include <string.h>

#define BUF_SIZE 256

int main(int argc, char* argv[]) {
    if (argc < 4) {
        printf("Usage: %s [user] [hostname] [shell]\n", argv[0]);
        return 1;
    }

    int pipefd[2];
    pid_t pid;
    char buf[BUF_SIZE];

    if (pipe(pipefd) == -1) {
        perror("pipe");
        return 1;
    }

    pid = fork();
    if (pid == -1) {
        perror("fork");
        return 1;
    }

    if (pid == 0) {  // child process
        close(pipefd[0]);  // close unused read end
        dup2(pipefd[1], STDOUT_FILENO);  // redirect stdout to write end of pipe
        char *args[] = {"ssh", argv[1], "@", argv[2], argv[3], NULL};
        execvp("ssh", args);
        return 0;
    } else {  // parent process
        close(pipefd[1]);  // close unused write end
        while (read(pipefd[0], buf, BUF_SIZE) > 0) {
            printf("%s", buf);
            memset(buf, 0, BUF_SIZE);
            //do stuff with the read memory
        }
    }
    return 0;
}
