#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int value;
    struct Node *left;
    struct Node *right;
} Node;

typedef struct {
    Node *root;
    int size;
} Set;

void createNode(Set *set, int value) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->value = value;
    newNode->left = NULL;
    newNode->right = NULL;
}

void setAdd(Set *set, int value) {}

int main() {


    return 0;
}