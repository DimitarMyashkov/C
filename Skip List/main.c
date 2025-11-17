#include <stdio.h>
#include <stdlib.h>

#define MAX_LEVEL 15
#define P 0.5

typedef struct Node {
    int key;
    struct Node *forward[];
} Node;

typedef struct {
    Node *header;
    int level;
    int size;
} SkipList;

int randomLevel() {
    int lvl = 1;
    while ((rand() / (double)RAND_MAX) < P && lvl < MAX_LEVEL) {
        lvl++;
    }

    return lvl;
}

Node* createNode(int key, int level) {
    Node* n = (Node*) malloc(sizeof(Node) + level * sizeof(Node*));
    if (!n) {
        printf("memory error\n");
        exit(1);
    }
    n->key = key;
    for (int i = 0; i < level; i++)
        n->forward[i] = NULL;
    return n;
}

void init(SkipList *sl) {
    sl->level = 1;
    sl->size = 0;
    sl->header = createNode(0, MAX_LEVEL);
}

void insert(SkipList *sl, int key) {
    Node *update[MAX_LEVEL];
    Node *x = sl->header;

    for (int i = sl->level - 1; i >= 0; i--) {
        while (x->forward[i] && x->forward[i]->key < key)
            x = x->forward[i];
        update[i] = x;
    }

    x = x->forward[0];
    if (x && x->key == key)
        return;

    int lvl = randomLevel();
    if (lvl > sl->level) {
        for (int i = sl->level; i < lvl; i++)
            update[i] = sl->header;
        sl->level = lvl;
    }

    x = createNode(key, lvl);
    for (int i = 0; i < lvl; i++) {
        x->forward[i] = update[i]->forward[i];
        update[i]->forward[i] = x;
    }

    sl->size++;
}

int search(SkipList *sl, int key) {
    Node *x = sl->header;
    for (int i = sl->level - 1; i >= 0; i--) {
        while (x->forward[i] && x->forward[i]->key < key)
            x = x->forward[i];
    }
    x = x->forward[0];
    return (x && x->key == key);
}

void delete(SkipList *sl, int key) {
    Node *update[MAX_LEVEL];
    Node *x = sl->header;

    for (int i = sl->level - 1; i >= 0; i--) {
        while (x->forward[i] && x->forward[i]->key < key)
            x = x->forward[i];
        update[i] = x;
    }

    x = x->forward[0];

    if (!x || x->key != key) {
        printf("element not found\n");
        return;
    }

    for (int i = 0; i < sl->level; i++) {
        if (update[i]->forward[i] != x) {
            break;
        }
        update[i]->forward[i] = x->forward[i];
    }

    free(x);

    while (sl->level > 1 && sl->header->forward[sl->level - 1] == NULL) {
        sl->level--;
    }

    sl->size--;
}

void printList(SkipList *sl) {
    Node *x = sl->header->forward[0];
    while (x) {
        printf("%d", x->key);
        x = x->forward[0];
        if (x) printf(" ");
    }
    printf("\n");
}

void freeList(SkipList *sl) {
    Node *cur = sl->header;
    while (cur) {
        Node *next = cur->forward[0];
        free(cur);
        cur = next;
    }
}

void printMenu() {
    printf("\n Skip List \n");
    printf("I - insert node \n");
    printf("D - delete node \n");
    printf("S - search for node \n");
    printf("P - print all nodes \n");
    printf("choose an option: ");
}

int main() {
    SkipList sl;
    init(&sl);

    char command;
    int x;

    printMenu();
    while (scanf(" %c", &command) != EOF) {
        if (command == 'I') {
            printf("insert value of the node");
            scanf("%d", &x);
            insert(&sl, x);
            printMenu();
        } else if (command == 'D') {
            printf("insert target value");
            scanf("%d", &x);
            delete(&sl, x);
            printMenu();
        } else if (command == 'S') {
            printf("insert target value");
            scanf("%d", &x);
            if (search(&sl, x)) {
                printf("FOUND\n");
            } else {
                printf("NOT FOUND\n");
            }
            printMenu();
        } else if (command == 'P') {
            printList(&sl);
            printMenu();
        } else {
            break;
        }
    }

    freeList(&sl);
    return 0;
}
