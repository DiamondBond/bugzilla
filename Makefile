CC = g++
CFLAGS = -Ofast

all:
	g++ -Ofast bugzilla.cpp -o bugzilla.o

clean:
	rm bugzilla.o

