## Makefile

CC = gcc -std=gnu99 -g -Wall


playshell: main.c shellserver.c shellserver.h
	$(CC) main.c shellserver.c -lmysqlclient -o playshell


testfile: test.c shellserver.c shellserver.h
	$(CC) test.c shellserver.c -lmysqlclient -o testfile

clean:
	rm -f *.o playshell testfile
