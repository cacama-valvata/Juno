#ifndef PLAYERCLIENT_H
#define PLAYERCLIENT_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "wireguard.h"

int get_words(char ***inp);
void connectclient(char* pubkey, char* user, char* host, char* command, char* hkeys, char* buf);
void wgkeygen(char *pubkeyz, char *privkeyz);
int check_key(char *pubkey, char *privkey);
void process_config(const char* file_name, const char* search_str, const char* replace_str);

#endif /* PLAYERCLIENT_H */

