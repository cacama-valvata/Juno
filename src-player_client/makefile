## Makefile

CC = gcc -std=gnu99 -g -Wall
exe_file = playerclient

all: $(exe_file)

$(exe_file): playerclientNOlibshh.c wireguard.h wireguard.c	
	$(CC) playerclientNOlibshh.c wireguard.c -o $(exe_file)

clean:
	rm -f *.o $(exe_file)
