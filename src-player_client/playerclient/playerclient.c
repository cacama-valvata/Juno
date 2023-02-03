#include "playerclient.h"
#define BUF_SIZE 256

//init the connection and allow user to mess around in shell
void connectclient(int argc, char *argv[])
{
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

void wgkeygen(char *pubkeyz, char *privkeyz){


  // generate public key (if not already existing)

  // Generate a WireGuard public key
  wg_key privkey;
  wg_generate_private_key(privkey);

  wg_key_b64_string pubkeys;
  wg_key_to_base64(pubkeys, privkey);

  //generate and maybe send to file
  printf("here is my public key %s\n", pubkeys);
  memcpy(pubkeyz, pubkeys, 32);
  memcpy(privkeyz, privkey, 32);


  return;

}


//checking for key file basic, needs to be modified if reading wg file
int check_key(char *pubkey, char *privkey) {
    FILE *file;
   
    // read file
    file = fopen("/etc/wireguard/wg0.conf", "r");
    if (file == NULL) {
        return 0;
    }

    //TO DO: CHANGE KEY PARSE METHOD
    fgets(pubkey, 32, file);
    fgets(privkey, 32, file);

    fclose(file);  

    //cut off newline and save
    pubkey[strcspn(pubkey, "\n")] = 0;
    privkey[strcspn(privkey, "\n")] = 0;
    return((strlen(pubkey) > 30) && (strlen(privkey) > 30));
}

void process_config(const char* file_name, const char* search_str, const char* replace_str) {
    FILE* fp = fopen(file_name, "r+");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    // Get the length of the search string
    int search_len = strlen(search_str);

    // Allocate memory for the buffer
    char* buffer = (char*) malloc(search_len);

    // Read the file one character at a time
    int c;
    while ((c = fgetc(fp)) != EOF) {
        // Check if the current character is the same as the first character of the search string
        if (c == search_str[0]) {
            // Read the next search_len characters into the buffer
            fread(buffer, 1, search_len, fp);

            // Check if the buffer matches the search string
            if (strncmp(buffer, search_str, search_len) == 0) {
                // Move the file pointer back to the beginning of the search string
                fseek(fp, -search_len, SEEK_CUR);

                // Write the replace string
                fwrite(replace_str, 1, strlen(replace_str), fp);

                // Move the file pointer to the end of the replace string
                fseek(fp, strlen(replace_str) - search_len, SEEK_CUR);
            } else {
                // Move the file pointer back to the beginning of the buffer
                fseek(fp, -search_len, SEEK_CUR);
            }
        }
    }

    // Close the file and free the buffer
    fclose(fp);
    free(buffer);

    // attempt to bring up wiregaurd daemon 
}

