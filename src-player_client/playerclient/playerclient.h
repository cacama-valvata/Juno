#ifndef PLAYERCLIENT_H
#define PLAYERCLIENT_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "wireguard.h"


void connectclient(int argc, char *argv[]);
void wgkeygen(char *pubkeyz, char *privkeyz);
int check_key(char *pubkey, char *privkey);
void process_config(const char* file_name, const char* search_str, const char* replace_str);

#endif /* PLAYERCLIENT_H */

