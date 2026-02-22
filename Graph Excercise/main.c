#include <stdio.h>
#include <stdlib.h>

#define MAX 100

typedef struct {
    int V;
    int directed;
    int adj[MAX][MAX];
} Graph;

int dfs_directed(Graph *g, int v, int visited[], int stack[]) {
    visited[v] = 1;
    stack[v] = 1;

    for (int i = 0; i < g->V; i++) {
        if (g->adj[v][i]) {
            if (!visited[i] && dfs_directed(g, i, visited, stack)) {
                return 1;
            } else if (stack[i]) {
                return 1;
            }
        }
    }

    stack[v] = 0;
    return 0;
}

int dfs_undirected(Graph *g, int v, int visited[], int parent) {
    visited[v] = 1;

    for (int i = 0; i < g->V; i++) {
        if (g->adj[v][i]) {
            if (!visited[i]) {
                if (dfs_undirected(g, i, visited, v)) {
                    return 1;
                }
            } else if (i != parent) {
                return 1;
            }
        }
    }

    return 0;
}

int is_cyclical(Graph *g) {
    int visited[MAX] = {0};
    int stack[MAX] = {0};

    for (int i = 0; i < g->V; i++) {
        if (!visited[i]) {
            if (g->directed) {
                if (dfs_directed(g, i, visited, stack)) {
                    return 1;
                }
            } else {
                if (dfs_undirected(g, i, visited, -1)) {
                    return 1;
                }
            }
        }
    }

    return 0;
}

void topo_dfs(Graph *g, int v, int visited[], int result[], int *index) {
    visited[v] = 1;

    for (int i = 0; i < g->V; i++) {
        if (g->adj[v][i] && !visited[i]) {
            topo_dfs(g, i, visited, result, index);
        }
    }

    result[(*index)--] = v;
}

void topological_sort(Graph *g) {
    int visited[MAX] = {0};
    int result[MAX] = {0};
    int index = g->V - 1;

    for (int i = 0; i < g->V; i++) {
        if (!visited[i]) {
            topo_dfs(g, i, visited, result, &index);
        }
    }

    printf("Topological order: ");

    for (int i = 0; i < g->V; i++) {
        printf("%d ", result[i]);
    }
    printf("\n");
}

int is_reachable(Graph *g, int start, int end) {
    int visited[MAX] = {0};
    int queue[MAX];
    int front = 0, rear = 0;

    visited[start] = 1;
    queue[rear++] = start;

    while (front < rear) {
        int v = queue[front++];

        if (v == end) {
            return 1;
        }

        for (int i = 0; i < g->V; i++) {
            if (g->adj[v][i] && !visited[i]) {
                visited[i] = 1;
                queue[rear++] = i;
            }
        }
    }

    return 0;
}

void add_edge(Graph *g, int src, int dest) {
    g->adj[src][dest] = 1;

    if (!g->directed) {
        g->adj[dest][src] = 1;
    }
}

int main() {
    Graph g;
    g.V = 6;
    g.directed = 1;

    for (int i = 0; i < g.V; i++) {
        for (int j = 0; j < g.V; j++) {
            g.adj[i][j] = 0;
        }
    }

    add_edge(&g, 0, 1);
    add_edge(&g, 0, 2);
    add_edge(&g, 1, 3);
    add_edge(&g, 2, 3);
    add_edge(&g, 3, 4);
    add_edge(&g, 4, 5);

    if (is_cyclical(&g)) {
        printf("Cyclical order\n");
    } else {
        printf("Uncyclical order\n");
    }

    if (!is_cyclical(&g)) {
        topological_sort(&g);
    }

    int start = 0;
    int end = 5;

    if (is_reachable(&g, start, end)) {
        printf("Reachable from %d to %d \n", start, end);
    } else {
        printf("Unreachable from %d to %d \n", start, end);
    }

    return 0;
}