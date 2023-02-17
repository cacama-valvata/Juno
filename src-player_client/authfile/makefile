## Makefile

CC = gcc -std=gnu99 -g -Wall


authshell: main.c smallsh_ssh_auth.c smallssh_ssh_auth.h
	$(CC) main.c smallsh_ssh_auth.c -lmysqlclient -o authshell


testfile: test.c smallsh_ssh_auth.c smallssh_ssh_auth.h
	$(CC) test.c smallsh_ssh_auth.c -o testfile

clean:
	rm -f *.o authshell testfile
