#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int vertex;
    struct Node *next;
} Node;

Node **graph;
int *visited;

void addEdge(int from, int to) {
    Node *newNode = (Node*)malloc(sizeof(Node));
    newNode->vertex = to;
    newNode->next = graph[from];
    graph[from] = newNode;
}

int dfs(int current, int target) {
    if (current == target) {
        return 1;
    }

    visited[current] = 1;

    Node *temp = graph[current];

    while (temp != NULL) {
        int next = temp->vertex;

        if (!visited[next]) {
            if (dfs(current, temp->vertex)) {
                return 1;
            }
        }

        temp = temp->next;
    }

    return 0;
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    graph = (Node**)malloc(sizeof(Node*)*n);
    visited = (int*)malloc(sizeof(int)*n);

    for (int i = 0; i < n; i++) {
        graph[i] = NULL;
    }

    for (int i = 0; i < m; i++) {
        int a, b;
        scanf("%d %d", &a, &b);

        addEdge(a, b);
    }

    int q;
    scanf("%d", &q);

    for (int i = 0; i < q; i++) {
        int x, y;
        scanf("%d %d", &x, &y);

        for (int j = 0; j < n; j++) {
            visited[j] = 0;
        }

        if (dfs(x, y)) {
            printf("YES\n");
        } else {
            printf("NO\n");
        }
    }

    for (int i = 0; i < n; i++) {
        Node *temp = graph[i];

        while (temp != NULL) {
            Node *toDelete = temp;
            temp = temp->next;
            free(toDelete);
        }
    }

    free(graph);
    free(visited);

    return 0;
}