taskmanager.o: taskmanager.c processes.h
	gcc -c taskmanager.c -o taskmanager.o

processes.o: processes.c processes.h
	gcc -c processes.c -o processes.o

taskmanager: taskmanager.o processes.o
	gcc taskmanager.o processes.o -o taskmanager

clean:
	rm -f taskmanager.o processes.o taskmanager
