#ifndef SHELLAUTH_H
#define SHELLAUTH_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>


int read_credentials(char *username, char *password);
void execdb(char *username, char *password, char* query, char* buf);
char *append_p(const char *str);



#endif /* SHELLAUTH_H */
