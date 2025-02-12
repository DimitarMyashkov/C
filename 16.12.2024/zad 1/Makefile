all: main

main: main.o quadraticroots.o
	gcc -o main main.o quadraticroots.o

main.o: main.c quadraticroots.h
	gcc -c main.c

quadraticroots.o: quadraticroots.c quadraticroots.h
	gcc -c quadraticroots.c

clean:
	rm -f *.o main
