## Makefile

CC = gcc -std=gnu17 -Wall
WG = wireguard_lib/contrib/embeddable-wg-library


all/build: build/authlookup build/playerclient build/junoshell

all/test: tests/test_authlookup tests/test_playerclient tests/test_junoshell

clean:
	rm -rf build/ tests/


# Build

build/authlookup: authlookup/main.c authlookup/authlookup.c authlookup/authlookup.h mysql-dev build/
	$(CC) authlookup/main.c authlookup/authlookup.c -lmysqlclient -o build/authlookup

build/playerclient: playerclient/main.c playerclient/playerclient.c playerclient/playerclient.h build/
	$(CC) playerclient/main.c playerclient/playerclient.c $(WG)/wireguard.c -I$(WG) -o build/playerclient

build/junoshell: junoshell/main.c junoshell/junoshell.c junoshell/junoshell.h mysql-dev build/
	$(CC) junoshell/main.c junoshell/junoshell.c -lmysqlclient -o build/junoshell

build/:
	mkdir -p build


# Test

tests/test_authlookup: authlookup/test.c authlookup/authlookup.c authlookup/authlookup.h mysql-dev tests/
	$(CC) authlookup/test.c authlookup/authlookup.c -lmysqlclient -o tests/test_authlookup

tests/test_player_client: playerclient/test.c playerclient/playerclient.c playerclient/playerclient.h tests/
	$(CC) playerclient/test.c playerclient/playerclient.c $(WG)/wireguard.c -I$(WG) -o tests/test_playerclient

tests/test_junoshell: junoshell/test.c junoshell/junoshell.c junoshell/junoshell.h mysql-dev tests/
	$(CC) junoshell/test.c junoshell/junoshell.c -lmysqlclient -o tests/test_junoshell

tests/:	
	mkdir -p tests


# Checks for both the header files and the library
# Dynamically linked - expects the library to be present at runtime
# If not there, install on apt distros with:
#	apt install libmysqlclient-dev
#	apt install libmysqlclient21
mysql-dev:
	test -f /usr/include/mysql/mysql.h
	ldconfig -p | grep mysqlclient.so.21
