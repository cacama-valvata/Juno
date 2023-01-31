## Makefile
CC = gcc --std=gnu99 -Wall


all: playerclient shellserver sshauth

playerclient.out: playerclientNOlibshh.c wireguard.h wireguard.c	
	$(CC) playerclientNOlibshh.c wireguard.c -o playerclient.out

shellserver.out: shellserver.c
	$(CC) shellserver.c -o shellserver.out

sshauth.out: smallsh_ssh_auth.c 
	$(CC) smallsh_ssh_auth.c -o sshauth.out

clean:
	rm -f *.o *.out
