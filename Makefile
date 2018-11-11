CC=g++
CFAGS= -Wall -std=c++1z -lcrypto -pthread
DEPS = download seed makeMtorrent

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $<

all: interface.cpp 2D-matching-algos.cpp test.cpp
	$(CC) -o 2Dmatching interface.cpp 2D-matching-algos.cpp test.cpp
