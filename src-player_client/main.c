/******************************
 * Program 3: SmallSh
 * Name: Casey Colley
 * Email: colleyc@oregonstate.edu
 * Date: 05/03/21
 * 
 * DRIVER FILE
 *****************************/
 
#include "header.h"
#include "wireguard.h"
 
 
struct command* newCommand (char* line) {
  struct command* C = malloc(sizeof(struct command));
  C->argc = 0;
  
  for (int i = 0; i < 512; i++) {  //FUCKING POINTERS BRO
    C->argv[i] = NULL;
  }
  
  char* saveptr;
  char* entry = strtok_r(line, " \n", &saveptr);
  C->call = calloc(strlen(entry)+1, sizeof(char));
  strcpy(C->call, entry);
  C->argv[0] = calloc(strlen(C->call)+1, sizeof(char));
  strcpy(C->argv[0], C->call);
  C->argc += 1;
  
  while ((entry = strtok_r(NULL, " \n", &saveptr)) != NULL) {
    if (! strcmp(entry, ">")) {  //output
      entry = strtok_r(NULL, " \n", &saveptr); //next arg is the dest
      C->output = calloc(strlen(entry)+1, sizeof(char));
      strcpy(C->output, entry);
    }
    else if (! strcmp(entry, "<")) {  //input
      entry = strtok_r(NULL, " \n", &saveptr); //next arg is the src
      C->input = calloc(strlen(entry)+1, sizeof(char));
      strcpy(C->input, entry);
    }
    /*else if (! strcmp(entry, "&")) {  //bg? but wont specify end
      C->background = 1;
      //continue;
    }*/
    else {
      C->argv[C->argc] = calloc(strlen(entry)+1, sizeof(char));
      strcpy(C->argv[C->argc], entry);
      C->argc += 1;
    }
  }
  
  if (! strcmp((C->argv[C->argc-1]), "&")) {  //is background process?
    C->background = 1;
    free(C->argv[C->argc -1]);
    C->argv[C->argc -1] = NULL;
    C->argc -= 1;
  }
  
  char* shpid = calloc(21, sizeof(char));  //max digits are 20 for a 64 bit system
  sprintf(shpid, "%d", getpid());
  
  for (int i = 1; i < C->argc; i++) {
    if (strstr(C->argv[i], "$$")) {
      int n = strlen(C->argv[i]) + strlen(shpid) - 2 /* $$ */ + 1 /* \0 */;
      char* newstring = calloc(n, sizeof(char));
      
      char* saveptr2;
      char* x;
      
      // strtok has strange behavior here
      if (C->argv[i][0] == '$') {  //if there is no text before the delim
        strcpy(newstring, shpid);
        if ((x = strtok_r(C->argv[i], "$", &saveptr2)) != NULL) {
          strcat(newstring, x);
        }
      }
      else {  //if there is text before the delim
        x = strtok_r(C->argv[i], "$", &saveptr2);
        strcpy(newstring, x);
        strcat(newstring, shpid);
        if ((x = strtok_r(NULL, "$", &saveptr2)) != NULL) {
          strcat(newstring, x);
        }
      }
      
      free(C->argv[i]);
      C->argv[i] = newstring;
    }
  }
  
  free(shpid);
  return C;
}

void deleteCommand (struct command* C) {
  free(C->call);
  C->call = NULL;
  for (int i = 0; i < C->argc; i++) {
    free(C->argv[i]);
    C->argv[i] = NULL;
  }
  if (C->input != NULL) {
    free(C->input);
    C->input = NULL;
  }
  if (C->output != NULL) {
    free(C->output);
    C->output = NULL;
  }
  C->argc = 0;
  C->background = 0;
  free(C);
  return;
}

void cd (struct command* C) {
  if (C->argv[1] == NULL) {  // i would include  || C->argv[1][0] == '~' but it breaks
    char* homepath = calloc(strlen(getenv("HOME")) + 1, sizeof(char));
    strcpy(homepath, getenv("HOME"));
    if (chdir(homepath) != 0) {
      printf("Error\n");
      fflush(stdout);
    }
    free(homepath);
  }
  else {
    if (chdir(C->argv[1]) != 0) {
      printf("Directory does not exist.\n");
      fflush(stdout);
    }
  }
  
  return;
}

void heartbeat( struct command* C){

  //send heartbeat to server 
  printf("here is your heartbeat :D\n");
  return;

}

void wgkeygen( struct command* C){


  // generate public key (if not already existing)

  // Generate a WireGuard public key
  wg_key privkey;
  wg_generate_private_key(privkey);

  wg_key_b64_string pubkeys;
  wg_key_to_base64(pubkeys, privkey);
  printf("here is my public key %s\n", pubkeys);

  return;
}

void wgupdate( struct command* C){

  //sending pub key for config
  printf("here is my public key %s\n", C->argv[1]);

  //use exec to scp generated file

  // read generated file
  char wg_config[4096];
  FILE *fp = fopen("/etc/wireguard/wg0.conf", "r");
  if (fp == NULL) {
      perror("fopen");
  }
  fread(wg_config, 1, sizeof(wg_config), fp);
  fclose(fp);

  //recieve config
  printf("here is your config: %s", wg_config);


  

  return;
}

void wgsend( struct command* C){


  // Read in the WireGuard configuration from a file
  char wg_config[4096];
  FILE *fp = fopen("/etc/wireguard/wg0.conf", "r");
  if (fp == NULL) {
      perror("fopen");
  }
  fread(wg_config, 1, sizeof(wg_config), fp);
  fclose(fp);

  //send config
  printf("Wireguard Config: %s", wg_config);

  return;
}


void status (struct laststat* laststatus) {
  if (laststatus->status == -5 && laststatus->signal == -5) {
    // no previously applicable process
    printf("No previous process to report on.\n");
    fflush(stdout);
    return;
  }
  
  if (laststatus->status != -5) {
    printf("The last process exited normally with status %d.\n", laststatus->status);
    fflush(stdout);
  }
  else if (laststatus->signal != -5) {
    printf("The last process terminated abnormally with signal %d.\n", laststatus->signal);
    fflush(stdout);
  }
}

void other(struct command* C, int** activechilds, struct laststat* laststatus) {
  
  pid_t spawnpid = -5;
  spawnpid = fork();
  int childstatus;
  
  switch (spawnpid) {
    case -1:
      printf("Error forking child.\n");
      fflush(stdout);
      
    case 0: 
      // INPUT REDIRECTION
      if (C->input != NULL) {  //is there input to be redirected?
        int inputfile = open(C->input, O_RDONLY, 0640);  //grab fileno of inputfile
        if (inputfile == -1) {
          printf("Could not process command, input file does not exist.\n");
          fflush(stdout);
          exit(EXIT_FAILURE);
        }
        dup2(inputfile, 0); //redirect stdin to inputfile
        close(inputfile);  //close inputfile
      }
      else if (C->background) {
        int devnullin = open("/dev/null", O_RDONLY);
        dup2(devnullin, 0);
        close(devnullin);
      }
      
      // OUTPUT REDIRECTION  
      if (C->output != NULL) {  //is there output to be redirected?
        int outputfile = open(C->output, O_WRONLY | O_CREAT | O_APPEND, 0640);
        dup2(outputfile, 1); //redirect stdout to outputfile
        close(outputfile);  //close outputfile
      }
      else if (C->background) {
        int devnullout = open("/dev/null", O_WRONLY);
        dup2(devnullout, 1);
        close(devnullout);
      }
      
      // hypothetically these work, but really they just run on DFL behavior
      if (C->background) {
        signal(SIGINT, SIG_IGN);
        struct sigaction ignore_action = {{0}};
        ignore_action.sa_handler = SIG_IGN;
        sigaction(SIGTSTP, &ignore_action, NULL);
      }
      else {
        signal(SIGINT, SIG_DFL);
        struct sigaction ignore_action = {{0}};
        ignore_action.sa_handler = SIG_IGN;
        sigaction(SIGTSTP, &ignore_action, NULL);
      }

      // EXECVP CALL
      execvp(C->call, C->argv);
      printf("Error with executing command.\n");
      fflush(stdout);
      exit(EXIT_FAILURE);
      
    default:
      if (C->background == 1) {  //background process
        printf("Beginning process %d in the background.\n", spawnpid);
        fflush(stdout);
        
        for (int i = 0; i < 20; i++) {
          if (activechilds[i] == NULL) {
            activechilds[i] = malloc(1 * sizeof(int));
            *(activechilds[i]) = spawnpid;
            break;
          }
        }
      }
      else {  //foreground process
        spawnpid = waitpid(spawnpid, &childstatus, 0);
        
        //setting for later call to status
        laststatus->status = -5;
        laststatus->signal = -5;
        if (WIFEXITED(childstatus)) {
          laststatus->status = WEXITSTATUS(childstatus);
        }
        else {
          laststatus->signal = WTERMSIG(childstatus);
        }
        
        if (! WIFEXITED(childstatus)) {
          printf("Uh oh spaghetti-o's\n");
          fflush(stdout);
        }
      }
      
      //printf("Yeehaw.\n");
  }
  
}

int menu(int** activechilds, struct laststat* laststatus) {  //start of commandline ':'

  //check for completion of child processes
  for (int i = 0; i < 20; i++) {
    if (activechilds[i] != NULL) {    
      int childpid = 0, childstatus;
      childpid = waitpid(*(activechilds[i]), &childstatus, WNOHANG);
      if (childpid != 0) {
        if(WIFEXITED(childstatus)) {
          printf("Child process %d exited normally with status %d.\n", childpid, WEXITSTATUS(childstatus));
        }
        else {
          printf("Child process %d exited abnormally due to signal %d.\n", childpid, WTERMSIG(childstatus));
        }
        free(activechilds[i]);
        activechilds[i] = NULL;
      }
    }
  }

  printf(":");
  fflush(stdout);
  
  char* line = calloc(2048+1, sizeof(char));
  //scanf("%s\n", line);
  fgets(line, 2048, stdin);
  
  
  if (line[0] == '#' || line[0] == '\n' || strlen(line) == 0) {
    // third condition is for SIGINT at command line. segfault otherwise
    free(line);
    return 0;
  }
  
  struct command* C = newCommand(line);
  free(line);
  
  if (fgmode) {
    C->background = 0;
  }

  if (! strcmp(C->call, "exit")) {
    deleteCommand(C);
    return 1;
    
  }
  else if (! strcmp(C->call, "cd")) {
    cd(C);
    
  }

  else if (! strcmp(C->call, "heartbeat")) {
    heartbeat(C);
  }

  else if (! strcmp(C->call, "wgkeygen")) {
    wgkeygen(C);
  }

  else if (! strcmp(C->call, "wgsend")) {
    wgsend(C);
  }

  else if (! strcmp(C->call, "wgupdate")) {
    wgupdate(C);
  }


  else if (! strcmp(C->call, "status")) {
    status(laststatus);
    
  }
  else {  //any other command passed to exec
    other(C, activechilds, laststatus);
    
  }
  
  deleteCommand(C);
  return 0;
}



void handle_SIGINT(int signo){
  write(STDOUT_FILENO, "\n", 1);
}

void handle_SIGTSTP(int signo) {
  write(STDOUT_FILENO, "\n", 1);
  
  if (fgmode == 1) {
    fgmode = 0;
    write(STDOUT_FILENO, "Exiting foreground-only mode.\n", 30);
  }
  else {
    fgmode = 1;
    write(STDOUT_FILENO, "Entering foreground-only mode.\n", 31);
  }
  //fgmode = (fgmode + 1) % 2;
}

 
int main() {

  struct sigaction SIGINT_action = {{0}};
  struct sigaction SIGTSTP_action = {{0}};
  //struct sigaction ignore_action = {{0}};
  
  SIGINT_action.sa_handler = handle_SIGINT;
  sigfillset(&SIGINT_action.sa_mask);
  SIGINT_action.sa_flags = 0;
  sigaction(SIGINT, &SIGINT_action, NULL);
  
  SIGTSTP_action.sa_handler = handle_SIGTSTP;
  sigfillset(&SIGTSTP_action.sa_mask);
  SIGTSTP_action.sa_flags = 0;
  sigaction(SIGTSTP, &SIGTSTP_action, NULL);
 
  //ignore_action.sa_handler = SIG_IGN;

  int** activechilds = malloc(20 * sizeof(int*));
  struct laststat* laststatus = malloc(1 * sizeof(struct laststat));
  laststatus->status = -5;
  laststatus->signal = -5;

  int q = 0;
  while (q != 1) {
    q = menu(activechilds, laststatus);
  }
  printf("\n");
  fflush(stdout);

  //catch any remaining child processes that need to be freed
  for (int i = 0; i < 20; i++) {
    if(activechilds[i] == NULL) {
      free(activechilds[i]);
      activechilds[i] = NULL;
    }
  }
  free(activechilds);
  free(laststatus);
  return EXIT_SUCCESS;
}
 