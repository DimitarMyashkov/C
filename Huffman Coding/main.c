#include <stdio.h>
#include <stdlib.h>

typedef unsigned int uint;

typedef struct Node {
    char value;
    int freq;
    struct Node *left, *right;
} Node;

Node *makeNode(char ch, int freq, Node *left, Node *right) {
    Node *n = malloc(sizeof(Node));
    n->value = ch;
    n->freq = freq;
    n->left = left;
    n->right = right;
}

Node *extractMin(Node *nodes[], int *size){
    int min = 0;
    for (int i = 0; i < *size; i++) {
        if (nodes[i]->freq < nodes[min]->freq) {
            min = i;
        }
    }

    Node *res = nodes[min];
    nodes[min] = nodes[*size - 1];
    (*size)--;

    return res;
}

Node *buildTree(uint size) {
    Node *nodes = malloc(sizeof(Node*));

    for (uint i = 0 ; i < size; i++) {
        
    }
}

void printCodes(Node *root, int code[], int depth) {
    if (root->left) {
        code[depth] = 0;
        printCodes(root->left, code, depth + 1);
    }
    if (root->right) {
        code[depth] = 1;
        printCodes(root->right, code, depth + 1);
    }
    if (!root->left && !root->right) {
        printf("%c", root->value);
        for (int i = 0; i < depth; i++) {
            printf("%d", code[i]);
        }
        printf("\n");
    }
}



int main() {


    return 0;
}
