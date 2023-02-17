## Makefile

CC = gcc -std=gnu99 -g -Wall


authlookup: main.c authlookup.c authlookup.h
	$(CC) main.c authlookup.c -lmysqlclient -o authlookup


testfile: test.c authlookup.c authlookup.h
	$(CC) test.c authlookup.c -lmysqlclient -o testfile

clean:
	rm -f *.o authlookup testfile
