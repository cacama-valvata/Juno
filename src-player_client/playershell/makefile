## Makefile

CC = gcc -std=gnu99 -g -Wall


playshell: main.c shellserver.c shellserver.h
	$(CC) main.c shellserver.c -o playshell


testfile: test.c shellserver.c shellserver.h
	$(CC) test.c shellserver.c -o testfile

clean:
	rm -f *.o authshell testfile
