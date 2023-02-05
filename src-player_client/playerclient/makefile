## Makefile

CC = gcc -std=gnu99 -g -Wall


client: main.c playerclient.c playerclient.h wireguard.c wireguard.h
	$(CC) main.c playerclient.c wireguard.c -o client


testfile: test.c playerclient.c playerclient.h
	$(CC) test.c playerclient.c -o testfile

clean:
	rm -f *.o client testfile