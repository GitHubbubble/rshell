CFLAGS = -Wall -Werror -ansi -pedantic

all: rshell ls

rshell: rshell.cpp bin
	g++ $(CFLAGS) rshell.cpp -o bin/rshell

ls: ls.cpp bin
	g++ $(CFLAGS) ls.cpp -o bin/ls

bin:
	mkdir bin
