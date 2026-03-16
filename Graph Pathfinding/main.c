#include <stdio.h>
#include <stdlib.h>

#define MAX_NODES 100

typedef struct {
    int adj[MAX_NODES][MAX_NODES];
    int weights[MAX_NODES][MAX_NODES];
    int n;
} Graph;

typedef struct {
    int path[MAX_NODES];
    int size;
} Path;


Graph* create_graph(int n) {
    Graph* g = (Graph*)malloc(sizeof(Graph));
    g->n = n;
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            g->adj[i][j] = 0;
            g->weights[i][j] = 0;
        }
    }
    return g;
}

void add_edge(Graph* g, int u, int v) {
    g->adj[u][v] = 1;
    g->adj[v][u] = 1;
    g->weights[u][v] = 1;
    g->weights[v][u] = 1;
}

void add_weighted_edge(Graph* g, int u, int v, int weight) {
    g->adj[u][v] = 1;
    g->adj[v][u] = 1;
    g->weights[u][v] = weight;
    g->weights[v][u] = weight;
}

void print_path(Path* p) {
    if (p->size == 0) {
        printf("Път не съществува\n");
        return;
    }
    for (int i = 0; i < p->size; i++) {
        printf("%d", p->path[i]);
        if (i < p->size - 1) printf(" -> ");
    }
    printf("\n");
}


int dfs_find(Graph* g, int current, int target, int visited[], Path* p) {
    visited[current] = 1;
    p->path[p->size++] = current;
    
    if (current == target) {
        return 1;
    }
    
    for (int i = 0; i < g->n; i++) {
        if (g->adj[current][i] && !visited[i]) {
            if (dfs_find(g, i, target, visited, p)) {
                return 1;
            }
        }
    }
    
    p->size--;
    return 0;
}

Path* dfs_path(Graph* g, int start, int end) {
    Path* p = (Path*)malloc(sizeof(Path));
    p->size = 0;
    
    int visited[MAX_NODES] = {0};
    dfs_find(g, start, end, visited, p);
    
    return p;
}


void dfs_shortest(Graph* g, int current, int target, int visited[], Path* current_path, Path* best_path) {
    visited[current] = 1;
    current_path->path[current_path->size++] = current;
    
    if (current == target) {
        if (best_path->size == 0 || current_path->size < best_path->size) {
            best_path->size = current_path->size;
            for (int i = 0; i < current_path->size; i++) {
                best_path->path[i] = current_path->path[i];
            }
        }
        current_path->size--;
        visited[current] = 0;
        return;
    }
    
    for (int i = 0; i < g->n; i++) {
        if (g->adj[current][i] && !visited[i]) {
            dfs_shortest(g, i, target, visited, current_path, best_path);
        }
    }
    
    current_path->size--;
    visited[current] = 0;
}

Path* dfs_shortest_path(Graph* g, int start, int end) {
    Path* current = (Path*)malloc(sizeof(Path));
    Path* best = (Path*)malloc(sizeof(Path));
    
    current->size = 0;
    best->size = 0;
    
    int visited[MAX_NODES] = {0};
    dfs_shortest(g, start, end, visited, current, best);
    
    free(current);
    return best;
}


void dfs_weighted(Graph* g, int current, int target, int visited[], 
                  Path* current_path, int current_cost, 
                  Path* best_path, int* best_cost) {
    visited[current] = 1;
    current_path->path[current_path->size++] = current;
    
    if (current == target) {
        if (*best_cost == -1 || current_cost < *best_cost) {
            *best_cost = current_cost;
            best_path->size = current_path->size;
            for (int i = 0; i < current_path->size; i++) {
                best_path->path[i] = current_path->path[i];
            }
        }
        current_path->size--;
        visited[current] = 0;
        return;
    }
    
    for (int i = 0; i < g->n; i++) {
        if (g->adj[current][i] && !visited[i]) {
            dfs_weighted(g, i, target, visited, current_path, current_cost + g->weights[current][i], best_path, best_cost);
        }
    }
    
    current_path->size--;
    visited[current] = 0;
}

Path* dfs_weighted_path(Graph* g, int start, int end) {
    Path* current = (Path*)malloc(sizeof(Path));
    Path* best = (Path*)malloc(sizeof(Path));
    
    current->size = 0;
    best->size = 0;
    
    int best_cost = -1;
    int visited[MAX_NODES] = {0};
    dfs_weighted(g, start, end, visited, current, 0, best, &best_cost);
    
    free(current);
    return best;
}


Path* bfs_path(Graph* g, int start, int end) {
    Path* p = (Path*)malloc(sizeof(Path));
    p->size = 0;
    
    int queue[MAX_NODES];
    int front = 0, rear = 0;
    
    int visited[MAX_NODES] = {0};
    int parent[MAX_NODES];
    
    for (int i = 0; i < g->n; i++) {
        parent[i] = -1;
    }
    
    visited[start] = 1;
    queue[rear++] = start;
    
    int found = 0;
    
    while (front < rear && !found) {
        int current = queue[front++];
        
        if (current == end) {
            found = 1;
            break;
        }
        
        for (int i = 0; i < g->n; i++) {
            if (g->adj[current][i] && !visited[i]) {
                visited[i] = 1;
                parent[i] = current;
                queue[rear++] = i;
            }
        }
    }
    
    if (found) {
        int current = end;
        int path_arr[MAX_NODES];
        int path_size = 0;
        
        while (current != -1) {
            path_arr[path_size++] = current;
            current = parent[current];
        }
        
        for (int i = 0; i < path_size; i++) {
            p->path[i] = path_arr[path_size - 1 - i];
        }
        p->size = path_size;
    }
    
    return p;
}


Path* bfs_shortest_path(Graph* g, int start, int end) {
    return bfs_path(g, start, end);
}


Path* dijkstra_path(Graph* g, int start, int end) {
    Path* p = (Path*)malloc(sizeof(Path));
    p->size = 0;
    
    int dist[MAX_NODES];
    int visited[MAX_NODES] = {0};
    int parent[MAX_NODES];
    
    for (int i = 0; i < g->n; i++) {
        dist[i] = 999999;
        parent[i] = -1;
    }
    dist[start] = 0;
    
    for (int count = 0; count < g->n; count++) {
        int u = -1;
        int min_dist = 999999;
        
        for (int i = 0; i < g->n; i++) {
            if (!visited[i] && dist[i] < min_dist) {
                min_dist = dist[i];
                u = i;
            }
        }
        
        if (u == -1) break;
        
        visited[u] = 1;
        
        for (int v = 0; v < g->n; v++) {
            if (g->adj[u][v] && !visited[v]) {
                if (dist[u] + g->weights[u][v] < dist[v]) {
                    dist[v] = dist[u] + g->weights[u][v];
                    parent[v] = u;
                }
            }
        }
    }
    
    if (dist[end] != 999999) {
        int current = end;
        int path_arr[MAX_NODES];
        int path_size = 0;
        
        while (current != -1) {
            path_arr[path_size++] = current;
            current = parent[current];
        }
        
        for (int i = 0; i < path_size; i++) {
            p->path[i] = path_arr[path_size - 1 - i];
        }
        p->size = path_size;
    }
    
    return p;
}


int main() {
    Graph* g = create_graph(6);
    add_edge(g, 0, 1);
    add_edge(g, 0, 2);
    add_edge(g, 1, 2);
    add_edge(g, 1, 3);
    add_edge(g, 2, 3);
    add_edge(g, 3, 4);
    add_edge(g, 4, 5);
    
    printf("\n===== Unweighted Graph =====\n\n");
    
    printf("DFS path (0 -> 5): ");
    Path* p1 = dfs_path(g, 0, 5);
    print_path(p1);
    free(p1);
    
    printf("Shortest DFS (0 -> 5): ");
    Path* p2 = dfs_shortest_path(g, 0, 5);
    print_path(p2);
    free(p2);
    
    printf("BFS path (0 -> 5): ");
    Path* p3 = bfs_path(g, 0, 5);
    print_path(p3);
    free(p3);
    
    printf("Shortest BFS (0 -> 5): ");
    Path* p4 = bfs_shortest_path(g, 0, 5);
    print_path(p4);
    free(p4);
    
    printf("\n===== Weighted Graph =====\n\n");
    
    Graph* gw = create_graph(6);
    add_weighted_edge(gw, 0, 1, 4);
    add_weighted_edge(gw, 0, 2, 2);
    add_weighted_edge(gw, 1, 2, 1);
    add_weighted_edge(gw, 1, 3, 5);
    add_weighted_edge(gw, 2, 3, 8);
    add_weighted_edge(gw, 3, 4, 2);
    add_weighted_edge(gw, 4, 5, 3);
    add_weighted_edge(gw, 2, 4, 10);
    
    printf("Shortest DFS with weight (0 -> 5): ");
    Path* p5 = dfs_weighted_path(gw, 0, 5);
    print_path(p5);
    free(p5);
    
    printf("Dijkstra (0 -> 5): ");
    Path* p6 = dijkstra_path(gw, 0, 5);
    print_path(p6);
    free(p6);
    
    free(g);
    free(gw);
    
    return 0;
}