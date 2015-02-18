CFLAGS = -Wall -Werror -ansi -pedantic

all: rshell ls cp

rshell: rshell.cpp bin
	g++ $(CFLAGS) rshell.cpp -o bin/rshell

ls: ls.cpp bin
	g++ $(CFLAGS) ls.cpp -o bin/ls

cp: cp.cpp bin
	g++ $(CFLAGS) cp.cpp -o bin/cp

bin:
	mkdir bin
