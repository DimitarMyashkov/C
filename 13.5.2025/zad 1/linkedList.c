#include "LinkedList.h"
#include <stdio.h>
#include <stdlib.h>

LinkedList init() {
    LinkedList newList = {
            .head = NULL,
            .size = 0
    };

    return newList;
}

static Node * createNode(Task value) {
    Node * newNode = malloc(sizeof(Node));
    if (newNode == NULL){
        printf("Error allocating memory\n");
        exit(0);
    }

    newNode->value = value;
    newNode->next = NULL;

    return newNode;
}

void pushFront(LinkedList * list, Task value) {
    Node * newNode = createNode(value);

    newNode->next = list->head;
    list->head = newNode;
    list->size++;
}

Node * getNode(LinkedList * list, uint index) {
    Node * currentNode = list->head;
    for (int i = 0; i < index; i++) {
        currentNode = currentNode->next;
    }
    return currentNode;
}

Task get(LinkedList * list, uint index) {
    Node * currentNode = getNode(list, index);
    return currentNode->value;
}

void push(LinkedList * list, uint index, Task value) {
    if (index > list->size) {
        printf("Index out of bounds \n");
        exit(1);
    }

    if (index == 0) {
        pushFront(list, value);
    } else {
        Node * prevNode = getNode(list, index - 1);
        Node * newNode = createNode(value);

        newNode->next = prevNode->next;
        prevNode->next = newNode;
        list->size++;
    }
}

void pushBack(LinkedList * list, Task value) {
    push(list, list->size, value);
    list->size++;
}

Task popFront(LinkedList * list) {
    Node * nodeToDelete = list->head;
    list->head = nodeToDelete->next;

    Task result = nodeToDelete->value;
    free(nodeToDelete);
    list->size--;

    return result;
}

Task pop(LinkedList * list, uint index) {
    if (index > list->size) {
        printf("Index out of bounds \n");
        exit(1);
    }

    if (index == 0) {
        popFront(list);
    } else {
        Node * prevNode = getNode(list, index - 1);
        Node * nodeToDelete = list->head;
        for (int i = 0; i < index; i++) {
            nodeToDelete = nodeToDelete->next;
        }

        prevNode->next = nodeToDelete->next;
        free(nodeToDelete);
        list->size--;
    }
}

Task popBack(LinkedList * list) {
    pop(list, (list->size - 1));
}

void set(LinkedList * list, uint index, Task value) {
    if (index > list->size) {
        printf("Index out of bounds \n");
        exit(1);
    }

    Node *nodeToChange = list->head;
    for (int i = 0; i < index; i++) {
        nodeToChange = nodeToChange->next;
    }

    nodeToChange->value = value;
}

void release(LinkedList * list);