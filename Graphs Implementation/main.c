#include <stdio.h>

#define MAX 10

int graph[MAX][MAX];
int n;

void initGraph (int vertices) {
    n = vertices;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            graph[i][j] = 0;
        }
    }
}

void addEdge(int u, int v) {
    graph[u][v] = 1;
    graph[v][u] = 1;
}

void readFromFile(char *filename) {
    FILE *f = fopen(filename, "r");
    if (f == NULL) {
        printf("error opening file");
        return;
    }

    fscanf(f, "%d", &n);
    initGraph(n);

    int u, v;
    while (fscanf(f, "%d %d", &u, &v) == 2) {
        addEdge(u, v);
    }

    fclose(f);
}

void printGraph() {
    printf("adjacency matrix\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", graph[i][j]);
        }
    }
    printf("\n");
}

int visited[MAX];

void DFS(int v) {
    visited[v] = 1;
    printf("%d", v);

    for (int i = 0; i < n; i++) {
        if (graph[v][i] == 1 && !visited[i]) {
            DFS(i);
        }
    }
}

int main() {
   readFromFile("graph.txt");
   printGraph();

   printf("\nDFS from vertex 0: ");
   DFS(0);

    return 0;
}
