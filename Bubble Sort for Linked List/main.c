#include <stdio.h>
#include <stdlib.h>

typedef int ListType;
typedef unsigned int uint;

typedef struct Node {
    ListType value;
    struct Node * next;
} Node;

typedef struct {
    Node * head;
    uint size;
} List;

List init() {
    List newList = {
            .head = NULL,
            .size = 0
    };

    return newList;
}

Node * createNode(ListType value) {
    Node *newNode = malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Error allocating memory\n");
        exit(0);
    }
    newNode->value = value;
    newNode->next = NULL;

    return newNode;
}

Node * getNode(List * list, uint index) {
    Node * currentNode = list->head;
    for (int i = 0; i < index; i++) {
        currentNode = currentNode->next;
    }
    return currentNode;
}

void push(List * list, uint index, ListType value) {
    if (index > list->size) {
        printf("Index out of bounds \n");
        exit(1);
    }

    if (index == 0) {
        Node * newNode = createNode(value);
        newNode->next = list->head;
        list->head = newNode;
        list->size++;
    } else {
        Node * prevNode = getNode(list, index - 1);
        Node * newNode = createNode(value);

        newNode->next = prevNode->next;
        prevNode->next = newNode;
        list->size++;
    }
}

void bubbleSortList(List *list) {
    if (list == NULL) {
        printf("List is NULL\n");
        return;
    }

    for (int i = 0; i < list->size - 1; i++) {
        Node *current = list->head;
        Node *nextNode = (Node *) current->next;
        for (int j = 0; j < list->size - i - 1; j++) {
            if (current->value > nextNode->value) {
                int temp = current->value;
                current->value = nextNode->value;
                nextNode->value = temp;
            }
            current = nextNode;
            nextNode = (Node *) nextNode->next;
        }
    }
}

int main(void) {
    List myList = init();
    push(&myList, 0, 5);
    push(&myList, 1, 3);
    push(&myList, 2, 8);
    push(&myList, 3, 1);
    push(&myList, 4, 4);
    printf("Unsorted list: ");
    for (int i = 0; i < myList.size; i++) {
        Node * node = getNode(&myList, i);
        printf("%d ", node->value);
    }
    printf("\n");

    bubbleSortList(&myList);

    printf("Sorted list: ");
    for (int i = 0; i < myList.size; i++) {
        Node * node = getNode(&myList, i);
        printf("%d ", node->value);
    }
    printf("\n");

    return 0;
}
