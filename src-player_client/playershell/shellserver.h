#ifndef SHELLSERVER_H
#define SHELLSERVER_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <mysql/mysql.h>


int read_credentials (char* username, char* password, char* host, char* credfile);
MYSQL_RES* query_pubkey (char* query);
void retrieve_conf(char* key, char* gameid);
char *append_p(const char *str);
void heartbeat (char* key);
void run_command (char* c);


#endif /* SHELLSERVER_H */
