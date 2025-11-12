#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node *next;
} Node;

typedef struct Stats {
    int swaps;
    int comparisons;
} Stats;

Stats *create_stats() {
    Stats *stats = malloc(sizeof(Stats));
    stats->swaps = 0;
    stats->comparisons = 0;
    return stats;
}

Node *newNode(int value) {
    Node *node = malloc(sizeof(Node));
    node->value = value;
    node->next = NULL;
    return node;
}

void addToEnd(Node **head, int value) {
    Node *node = newNode(value);
    if (*head == NULL) {
        *head = node;
        return;
    }
    Node *curr = *head;
    while (curr->next != NULL) {
        curr = curr->next;
    }
    curr->next = node;
}

void showList(Node *head) {
    while (head != NULL) {
        printf("%d ", head->value);
        head = head->next;
    }
    printf("\n");
}

void freeNodes(Node *head) {
    while (head != NULL) {
        Node *tmp = head;
        head = head->next;
        free(tmp);
    }
}

void bubbleSortValues(Node *head, Stats *stats) {
    if (head == NULL) {
        return;
    }
    int swapped = 0;
    Node *curr = NULL;
    Node *last = NULL;
    do {
        swapped = 0;
        curr = head;
        while (curr->next != last) {
            stats->comparisons = stats->comparisons + 1;
            if (curr->value > curr->next->value) {
                int tmp = curr->value;
                curr->value = curr->next->value;
                curr->next->value = tmp;
                stats->swaps = stats->swaps + 1;
                swapped = 1;
            }
            curr = curr->next;
        }
        last = curr;
    } while (swapped != 0);
}

void bubbleSortNodes(Node **head, Stats *stats) {
    if (*head == NULL) {
        return;
    }
    int swapped = 0;
    Node **curr = NULL;
    do {
        swapped = 0;
        curr = head;
        while ((*curr)->next != NULL) {
            stats->comparisons = stats->comparisons + 1;
            if ((*curr)->value > (*curr)->next->value) {
                Node *tmp = (*curr)->next;
                (*curr)->next = tmp->next;
                tmp->next = *curr;
                *curr = tmp;
                stats->swaps = stats->swaps + 1;
                swapped = 1;
            }
            curr = &((*curr)->next);
            if (*curr == NULL) {
                break;
            }
            if ((*curr)->next == NULL) {
                break;
            }
        }
    } while (swapped != 0);
}

Node *tailNode(Node *curr) {
    while (curr != NULL) {
        if (curr->next == NULL) {
            break;
        }
        curr = curr->next;
    }
    return curr;
}

Node *partitionList(Node *head, Node *end, Node **newHead, Node **newEnd, Stats *stats) {
    Node *pivot = end;
    Node *prev = NULL;
    Node *curr = head;
    Node *tail = pivot;
    Node *first = NULL;
    while (curr != pivot) {
        stats->comparisons = stats->comparisons + 1;
        if (curr->value < pivot->value) {
            if (first == NULL) {
                first = curr;
            }
            prev = curr;
            curr = curr->next;
        } else {
            if (prev != NULL) {
                prev->next = curr->next;
            }
            Node *tmp = curr->next;
            curr->next = NULL;
            tail->next = curr;
            tail = curr;
            curr = tmp;
            stats->swaps = stats->swaps + 1;
        }
    }
    if (first == NULL) {
        first = pivot;
    }
    *newHead = first;
    *newEnd = tail;
    return pivot;
}

Node *quickSort(Node *head, Node *end, Stats *stats) {
    if (head == NULL) {
        return head;
    }
    if (head == end) {
        return head;
    }
    Node *newHead = NULL;
    Node *newEnd = NULL;
    Node *pivot = partitionList(head, end, &newHead, &newEnd, stats);
    if (newHead != pivot) {
        Node *tmp = newHead;
        while (tmp->next != pivot) {
            tmp = tmp->next;
        }
        tmp->next = NULL;
        newHead = quickSort(newHead, tmp, stats);
        tmp = tailNode(newHead);
        tmp->next = pivot;
    }
    pivot->next = quickSort(pivot->next, newEnd, stats);
    return newHead;
}

void quickSortList(Node **head, Stats *stats) {
    *head = quickSort(*head, tailNode(*head), stats);
}

void fillList(Node **head, int *values, int size) {
    *head = NULL;
    int i = 0;
    for (i = 0; i < size; i = i + 1) {
        addToEnd(head, values[i]);
    }
}

void runBubbleTests() {
    printf("=== Bubble Sort ===\n");
    int vals[7] = {5,3,6,2,1,8,4};
    Node *head = NULL;
    Stats *stats = NULL;

    head = NULL;
    fillList(&head, vals, 7);
    stats = create_stats();
    printf("-- Swap Values --\nOriginal: ");
    showList(head);
    bubbleSortValues(head, stats);
    printf("Sorted:   ");
    showList(head);
    printf("Swaps: %d, Comparisons: %d\n\n", stats->swaps, stats->comparisons);
    freeNodes(head);
    free(stats);

    head = NULL;
    fillList(&head, vals, 7);
    stats = create_stats();
    printf("-- Swap Nodes --\nOriginal: ");
    showList(head);
    bubbleSortNodes(&head, stats);
    printf("Sorted:   ");
    showList(head);
    printf("Swaps: %d, Comparisons: %d\n\n", stats->swaps, stats->comparisons);
    freeNodes(head);
    free(stats);
}

void runQuickTests() {
    printf("=== Quick Sort ===\n");
    int vals[7] = {5,3,6,2,1,8,4};
    Node *head = NULL;
    Stats *stats = NULL;

    head = NULL;
    fillList(&head, vals, 7);
    stats = create_stats();
    printf("-- Swap Values --\nOriginal: ");
    showList(head);
    bubbleSortValues(head, stats);
    printf("Sorted:   ");
    showList(head);
    printf("Swaps: %d, Comparisons: %d\n\n", stats->swaps, stats->comparisons);
    freeNodes(head);
    free(stats);

    head = NULL;
    fillList(&head, vals, 7);
    stats = create_stats();
    printf("-- Swap Nodes --\nOriginal: ");
    showList(head);
    quickSortList(&head, stats);
    printf("Sorted:   ");
    showList(head);
    printf("Swaps: %d, Comparisons: %d\n\n", stats->swaps, stats->comparisons);
    freeNodes(head);
    free(stats);
}

int main(void) {
    runBubbleTests();
    runQuickTests();
    return 0;
}
