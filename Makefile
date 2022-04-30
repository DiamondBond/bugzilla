CC = g++
CFLAGS = -Ofast

all:
	g++ -Ofast bugzilla.cpp -o bugzilla.o

release:
	g++ bugzilla.cpp -o bugzilla_release.exe
	g++ bugzilla.cpp -o bugzilla_release.o

debug:
	g++ -g bugzilla.cpp -o bugzilla_debug.o

clean:
	rm bugzilla.o bugzilla.exe bugzilla_debug.o bugzilla_release.o bugzilla_release.exe

