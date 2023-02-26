#ifndef SHELLSERVER_H
#define SHELLSERVER_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <mysql/mysql.h>


char* sanitize_string(char* input_string);
int read_credentials (char* username, char* password, char* host, char* credfile);
MYSQL_RES* query_db (char* query);
char* parse_results (MYSQL_RES* res_users);
void retrieve_conf(char* key, char* gameid);
char *append_p(const char *str);
void heartbeat (char* key, char* userid);
void run_command (char* c, char* userid);


#endif /* SHELLSERVER_H */
