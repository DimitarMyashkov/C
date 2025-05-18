all: main.exe

main.exe: main.c linkedList.o
	gcc main.c linkedList.o -o main.exe

linkedList.o: linkedList.h linkedList.c
	gcc -c linkedList.c -o linkedList.o

clean:
	del -f *.o *.exe