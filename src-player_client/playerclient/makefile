## Makefile

CC = gcc -std=gnu99 -g -Wall
exe_file = playerclient

all: $(exe_file)

$(exe_file): main.c wireguard.h wireguard.c playerclient.h playerclient.c
	$(CC) main.c wireguard.c playerclient.c -o $(exe_file)

clean:
	rm -f *.o $(exe_file)
