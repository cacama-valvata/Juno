#ifndef SHELLAUTH_H
#define SHELLAUTH_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <mysql/mysql.h>


int read_credentials (char* username, char* password, char* host, char* credfile);
MYSQL_RES* query_pubkey (char* pubkey);
char* compare_users (MYSQL_RES* res_users);


#endif /* SHELLAUTH_H */
