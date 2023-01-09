## Makefile

CC = gcc -std=gnu99 -g -Wall
exe_file = smallsh

all: $(exe_file)

$(exe_file): main.c header.h wireguard.h wireguard.c	
	$(CC) main.c wireguard.c -o $(exe_file)

clean:
	rm -f *.o $(exe_file)
