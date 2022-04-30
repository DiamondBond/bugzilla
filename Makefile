CC = g++
CFLAGS = -Ofast

all:
	g++ -Ofast bugzilla.cpp -o bugzilla.exe
	cp bugzilla.exe bugzilla.o

debug:
	g++ -g bugzilla.cpp -o bugzilla_debug.o

clean:
	rm bugzilla.o bugzilla.exe bugzilla_debug.o

