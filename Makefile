CFLAGS = -Wall -Werror -ansi -pedantic

all: rshell ls cp

rshell: src/rshell.cpp bin
	g++ $(CFLAGS) src/rshell.cpp -o bin/rshell

ls: src/ls.cpp bin
	g++ $(CFLAGS) src/ls.cpp -o bin/ls

cp: src/cp.cpp bin
	g++ $(CFLAGS) src/cp.cpp -o bin/cp

bin:
	mkdir bin
