CFLAGS = -ansi -pedantic -Wall -Werror

bin/all: bin/ls | bin

bin/rshell: rshell.cpp | bin
	g++ -c $(CFLAGS) rshell.cpp

bin/ls: ls.cpp | bin
	g++ -c $(CFLAGS) ls.cpp

bin:
	mkdir bin

