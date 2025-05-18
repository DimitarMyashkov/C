#ifndef LINKED_LIST_H
#define LINKED_LIST_H

typedef struct Task {
    char name[100];
    enum TaskStatus { NEW, STARTED, FINISHED } status;
} Task;

typedef unsigned int uint;

typedef struct Node {
    Task value;
    struct Node * next;
} Node;

typedef struct {
    Node * head;
    uint size;
} LinkedList;

LinkedList init();

void pushBack(LinkedList * list, Task value);
void pushFront(LinkedList * list, Task value);
void push(LinkedList * list, uint index, Task value);

Task popBack(LinkedList * list);
Task popFront(LinkedList * list);
Task pop(LinkedList * list, uint index);

Node * getNode(LinkedList * list, uint index);

Task get(LinkedList * list, uint index);
void set(LinkedList * list, uint index, Task value);

void release(LinkedList * list);

#endif