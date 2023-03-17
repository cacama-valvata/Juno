#ifndef PLAYERCLIENT_H
#define PLAYERCLIENT_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "wireguard.h"

char *ssh_exec(char *hostname, char *username, char *private_key_path, char *command, char* hkey);
int get_words(char ***inp);
void wgkeygen(char *pubkeyz, char *privkeyz);
int check_key(char *pubkey, char *privkey);
void process_config(const char* file_name, const char* search_str, const char* replace_str);
char *replace_substring(const char *str, const char *sub, const char *replace)

#endif /* PLAYERCLIENT_H */

