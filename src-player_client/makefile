## Makefile

CC = gcc -std=gnu99 -g -Wall
exe_file = smallsh

all: $(exe_file)

$(exe_file): playershell.c header.h wireguard.h wireguard.c	
	$(CC) playershell.c wireguard.c -o $(exe_file)

clean:
	rm -f *.o $(exe_file)
