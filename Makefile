
CC=g++
CFLAGS= -Wall -pedantic -lncurses -std=c++14 -I -OFast
HEADERS= *.h
OBJS= *.o
SOURCES= *.cpp

all:
	$(CC) $(SOURCES) $(CFLAGS) -o Vonatjegy

.PHONY: clean

clean:
	rm -rf *o Vonatjegy
