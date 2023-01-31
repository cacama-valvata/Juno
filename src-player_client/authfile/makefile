## Makefile

CC = gcc -std=gnu99 -g -Wall
exe_file = authshell

all: $(exe_file)

$(exe_file): main.c smallsh_ssh_auth.c smallssh_ssh_auth.h
	$(CC) main.c smallsh_ssh_auth.c -o $(exe_file)

clean:
	rm -f *.o $(exe_file)
