#ifndef SHELLAUTH_H
#define SHELLAUTH_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>


void read_credentials(char *username, char *password);
void execdb(char *username, char *password, char* query, char* buf);



#endif /* SHELLAUTH_H */
