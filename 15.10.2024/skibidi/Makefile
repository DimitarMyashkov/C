all: skibidi.exe

skibidi.o: skibidi.c
	gcc -c skibidi.c -o skibidi.o

skibidi.exe: skibidi.o
	gcc -o skibidi.exe skibidi.o

clean:
	rm -f *.o *.exe