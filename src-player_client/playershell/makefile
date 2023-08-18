## Makefile

CC = gcc -std=gnu99 -g -Wall
exe_file = shellserver

all: $(exe_file)

$(exe_file): main.c shellserver.c shellserver.h 
	$(CC) main.c shellserver.c -o $(exe_file)

clean:
	rm -f *.o $(exe_file)
