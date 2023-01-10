/******************************
 * Program 3: juno shell client
 * Name: Casey Colley & Carter
 *
 * HEADER FILE
 *****************************/

 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <libssh/libssh.h>



struct command {
  char* call;
  char* argv[512];
  char* input;
  char* output;
  int argc;
  int background;
};

struct laststat {
  int status;
  int signal;
};

// Global variable for foreground-only mode
int fgmode = 0;


struct command* newCommand (char*);

void deleteCommand (struct command*);

void cd (struct command*);

void other (struct command*, int**,  struct laststat*);

void status (struct laststat*);

void handle_SIGINT (int);

void handle_SIGTSTP (int);

int menu (int**, struct laststat*);
