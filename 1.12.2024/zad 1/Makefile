CC = gcc
CFLAGS = -Wall -Wextra -pedantic -std=c11
TARGET = help.out
OBJS = main.o

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

clean:
	del $(TARGET) $(OBJS)
