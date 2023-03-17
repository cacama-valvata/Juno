#include "playerclient.h"

#define BUF_SIZE 256
#define INPUTLEN 1000

char *ssh_exec(char *hostname, char *username, char *private_key_path, char *command, char* hkey) 
{
    char *ssh_command = malloc(strlen(hostname) + strlen(username) + strlen(private_key_path) + strlen(command) + strlen(hkey) + 64);
    sprintf(ssh_command, "ssh -i %s %s@%s '%s %s'", private_key_path, username, hostname, command, hkey);
    //printf("%s\n",ssh_command);

    char buffer[1024];
    char *result = NULL;
    size_t result_size = 0;

    FILE *fp = popen(ssh_command, "r");
    if (fp == NULL) 
    {
        perror("Failed to execute command");
        exit(1);
    }

    while (fgets(buffer, 1024, fp) != NULL)
    {
        size_t buffer_size = strlen(buffer);
        result = realloc(result, result_size + buffer_size +1);
        if(result == NULL)
        {
            perror("Failed to allocate memory");
            exit(1);
        }
        strcpy(result + result_size, buffer);
        result_size += buffer_size;
    }

    pclose(fp);
    free(ssh_command);

    return result;
}


int get_words(char ***inp) 
{
    char input[INPUTLEN];
    int num_words = 0;
    
    // Prompt user to enter a sentence
    printf("Enter a command: ");
    fgets(input, INPUTLEN, stdin);
    
    // Remove newline character if present
    if (input[strlen(input) - 1] == '\n')
    {
        input[strlen(input) - 1] = '\0';
    }
    
    // Split sentence into words
    char *token = strtok(input, " ");
    while (token != NULL) 
    {
        // Reallocate memory for words array
        num_words++;
        *inp = (char **)realloc(*inp, num_words * sizeof(char *));
        
        // Allocate memory for new word and copy it 
        int len = strlen(token) + 1;
        (*inp)[num_words-1] = (char *)malloc(len * sizeof(char));
        strcpy((*inp)[num_words-1], token);
        
        // Get next token
        token = strtok(NULL, " ");
    }
    
    return num_words;
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

char *replace_substring(const char *str, const char *sub, const char *replace) {
    char *result, *p;
    int len, count = 0;

    // Get the length of the substring to be replaced
    len = strlen(sub);

    // Count the number of occurrences of the substring in the string
    for (p = strstr(str, sub); p != NULL; p = strstr(p + len, sub)) {
        count++;
    }

    // Allocate memory for the result string
    result = (char *) malloc(strlen(str) + count * (strlen(replace) - len) + 1);

    // Copy the string up to the first occurrence of the substring
    p = strstr(str, sub);
    strncpy(result, str, p - str);
    result[p - str] = '\0';

    // Copy the replacement string for each occurrence of the substring
    while (p != NULL) {
        strcat(result, replace);
        strcat(result, p + len);
        p = strstr(p + len, sub);
    }

    return result;
}

void process_config(const char* file_name, const char* search_str, const char* replace_str) {
    FILE* fp = fopen(file_name, "r+");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    // Get the length of the search string and replace string
    int search_len = strlen(search_str);
    int replace_len = strlen(replace_str);

    // Allocate memory for the buffer
    char* buffer = (char*) malloc(search_len);

    // Read the file one character at a time
    int c;
    long pos = 0;
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
                fwrite(replace_str, 1, replace_len, fp);

                // Adjust the current position in the file
                pos += replace_len - search_len;
                fseek(fp, pos, SEEK_CUR);
            } else {
                // Move the file pointer back to the beginning of the buffer
                fseek(fp, -search_len, SEEK_CUR);
                pos++;
            }
        } else {
            pos++;
        }
    }

    // Close the file and free the buffer
    fclose(fp);
    free(buffer);

    // attempt to bring up wiregaurd daemon 
}

