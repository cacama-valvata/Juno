#ifndef SHELLSERVER_H
#define SHELLSERVER_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>


int read_credentials(char *username, char *password);
void execdb(char *username, char *password, char* query, char* buf);
void retrieve_conf(char* key, char* username, char* password, char* gameid);
char *append_p(const char *str);
void heartbeat (char* key, char* username, char* password);
void wgupdate(char* key);
void wgsend();
void run_command (char* c);


#endif /* SHELLSERVER_H */
