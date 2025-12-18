#include <stdio.h>
#include <stdlib.h>

#define SLOTS 8
#define MAX_CHILDREN 32

typedef enum {
    BE_FIRST,
    BE_LAST,
    NOT_FIRST,
    NOT_LAST
} Constraint;

typedef struct {
    char *title;
    char *teacherName;
    int length;
    Constraint constraints[4];
    int constraintCount;
} Subject;

typedef struct {
    Subject* slots[SLOTS];
} Schedule;

typedef struct TreeNode {
    Schedule schedule;
    struct TreeNode* children[MAX_CHILDREN];
    int childCount;
} TreeNode;

Schedule copySchedule(Schedule* src) {
    Schedule dst;
    for (int i = 0; i < SLOTS; i++) {
        dst.slots[i] = src->slots[i];
    }
    return dst;
}

int isFree(Schedule* s, int start, int length) {
    if (start + length > SLOTS) {
        return 0;
    }
    for (int i = start; i < start + length; i++) {
        if (s->slots[i] != NULL) {
            return 0;
        }
    }
    return 1;
}

int satisfiesConstraints(Subject* subj, int start) {
    int end = start + subj->length - 1;

    for (int i = 0; i < subj->constraintCount; i++) {
        Constraint c = subj->constraints[i];
        if (c == BE_FIRST && start != 0) {
            return 0;
        }
        if (c == BE_LAST && end != SLOTS - 1) {
            return 0;
        }
        if (c == NOT_FIRST && start == 0) {
            return 0;
        }
        if (c == NOT_LAST && end == SLOTS - 1) {
            return 0;
        }
    }
    return 1;
}

Schedule placeSubject(Schedule* s, Subject* subj, int start) {
    Schedule newS = copySchedule(s);
    for (int i = start; i < start + subj->length; i++) {
        newS.slots[i] = subj;
    }
    return newS;
}

TreeNode* createNode(Schedule s) {
    TreeNode* n = malloc(sizeof(TreeNode));
    n->schedule = s;
    n->childCount = 0;
    return n;
}

int addSubject(TreeNode* node, Subject* subj) {
    if (node->childCount == 0) {
        int placed = 0;

        for (int i = 0; i < SLOTS; i++) {
            if (isFree(&node->schedule, i, subj->length) &&
                satisfiesConstraints(subj, i)) {

                Schedule ns = placeSubject(&node->schedule, subj, i);
                node->children[node->childCount++] = createNode(ns);
                placed = 1;
            }
        }
        return placed;
    }

    int newCount = 0;
    for (int i = 0; i < node->childCount; i++) {
        if (addSubject(node->children[i], subj))
            node->children[newCount++] = node->children[i];
    }

    node->childCount = newCount;
    return newCount > 0;
}

void printSchedule(Schedule* s) {
    for (int i = 0; i < SLOTS; i++) {
        if (s->slots[i] == NULL) printf("[----]");
        else printf("[%s, (%s)]", s->slots[i]->title, s->slots[i]->teacherName);
    }
    printf("\n");
}

void printTree(TreeNode* node, int depth) {
    for (int i = 0; i < depth; i++) printf("  ");
    printSchedule(&node->schedule);

    for (int i = 0; i < node->childCount; i++)
        printTree(node->children[i], depth + 1);
}

int main() {
    Schedule empty = {0};
    TreeNode* root = createNode(empty);


    Subject math = {"Math", "Martin Nedkov", 1, {}, 0};
    Subject history = {"History", "Stefan Yanakiev", 1, {BE_FIRST}, 1};
    Subject physics = {"Physics", "Yordan Tsonchev",2, {NOT_LAST}, 1};
    Subject bio = {"Biology", "Dimitar Myashkov", 1, {BE_FIRST}, 1};
    Subject chem = {"Chemistry", "Ivan Kostov", 1, {BE_FIRST}, 1};

    int choice;

    do {
        printf("\n===== SCHOOL SCHEDULE MENU =====\n");
        printf("1. Add Math (no constraints)\n");
        printf("2. Add History (BE_FIRST)\n");
        printf("3. Add Physics (NOT_LAST, length 2)\n");
        printf("4. Print schedule tree\n");
        printf("5. Demonstrate impossible schedule\n");
        printf("0. Exit\n");
        printf("Choice: ");
        scanf("%d", &choice);


        switch (choice) {
            case 1:
                addSubject(root, &math);
                printf("Math added\n");
                break;
            case 2:
                addSubject(root, &history);
                printf("History added\n");
                break;
            case 3:
                addSubject(root, &physics);
                printf("Physics added\n");
                break;
            case 4:
                printTree(root, 0);
                break;
            case 5: {
                TreeNode* badRoot = createNode(empty);
                addSubject(badRoot, &bio);
                if (!addSubject(badRoot, &chem))
                    printf("all branches pruned\n");
                else
                    printTree(badRoot, 0);
                break;
            }
            case 0:
                printf("exiting\n");
                break;
            default:
                printf("invalid choice\n");
        }
    } while (choice != 0);


    return 0;
}
