#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int ret =  execl("/usr/bin/mysql", "mysql", "-u", "root", "-proot", "-e", "Use Juno; SELECT count(*) as num_users FROM (SELECT userid from devices where ssh_pubkey = 'x') as useridlist;", (char *) NULL);

    if (ret == -1) {
        perror("execl failed");
        exit(1);
    }

    return 0;
}