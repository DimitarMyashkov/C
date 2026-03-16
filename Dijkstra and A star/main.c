#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_NODES 100
#define INF 999999


typedef struct {
    int adj[MAX_NODES][MAX_NODES];
    int weights[MAX_NODES][MAX_NODES];
    int n;
    int x[MAX_NODES];
    int y[MAX_NODES];
} Graph;

typedef struct {
    int path[MAX_NODES];
    int size;
    int total_cost;
} Path;

typedef struct {
    int node;
    int priority;
} PQItem;

typedef struct {
    PQItem items[MAX_NODES];
    int size;
} PriorityQueue;


Graph* create_graph(int n) {
    Graph* g = (Graph*)malloc(sizeof(Graph));
    g->n = n;
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            g->adj[i][j] = 0;
            g->weights[i][j] = 0;
        }
        g->x[i] = 0;
        g->y[i] = 0;
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

void set_node_position(Graph* g, int node, int x, int y) {
    g->x[node] = x;
    g->y[node] = y;
}

void print_path(Path* p) {
    if (p->size == 0) {
        printf("No existing path\n");
        return;
    }
    for (int i = 0; i < p->size; i++) {
        printf("%d", p->path[i]);
        if (i < p->size - 1) printf(" -> ");
    }
    printf(" (Cost: %d)\n", p->total_cost);
}


PriorityQueue* pq_create() {
    PriorityQueue* pq = (PriorityQueue*)malloc(sizeof(PriorityQueue));
    pq->size = 0;
    return pq;
}

void pq_insert(PriorityQueue* pq, int node, int priority) {
    pq->items[pq->size].node = node;
    pq->items[pq->size].priority = priority;
    pq->size++;
}

int pq_extract_min(PriorityQueue* pq) {
    int min_idx = 0;
    for (int i = 1; i < pq->size; i++) {
        if (pq->items[i].priority < pq->items[min_idx].priority) {
            min_idx = i;
        }
    }
    
    int node = pq->items[min_idx].node;
    
    for (int i = min_idx; i < pq->size - 1; i++) {
        pq->items[i] = pq->items[i + 1];
    }
    pq->size--;
    
    return node;
}

int pq_is_empty(PriorityQueue* pq) {
    return pq->size == 0;
}

int pq_contains(PriorityQueue* pq, int node) {
    for (int i = 0; i < pq->size; i++) {
        if (pq->items[i].node == node) {
            return 1;
        }
    }
    return 0;
}

void pq_free(PriorityQueue* pq) {
    free(pq);
}


int heuristic(Graph* g, int current, int target) {
    int dx = g->x[current] - g->x[target];
    int dy = g->y[current] - g->y[target];
    return (int)sqrt(dx * dx + dy * dy);
}


Path* dijkstra(Graph* g, int start, int end) {
    Path* p = (Path*)malloc(sizeof(Path));
    p->size = 0;
    p->total_cost = 0;
    
    int dist[MAX_NODES];
    int parent[MAX_NODES];
    int visited[MAX_NODES];
    
    for (int i = 0; i < g->n; i++) {
        dist[i] = INF;
        parent[i] = -1;
        visited[i] = 0;
    }
    dist[start] = 0;
    
    PriorityQueue* pq = pq_create();
    pq_insert(pq, start, 0);
    
    printf("\n[Dijkstra] Processed nodes: ");
    
    while (!pq_is_empty(pq)) {
        int u = pq_extract_min(pq);
        
        if (u == end) {
            printf("%d (Target found)", u);
            break;
        }
        
        if (visited[u]) continue;
        
        visited[u] = 1;
        printf("%d ", u);
        
        for (int v = 0; v < g->n; v++) {
            if (g->adj[u][v] && !visited[v]) {
                int new_dist = dist[u] + g->weights[u][v];
                
                if (new_dist < dist[v]) {
                    dist[v] = new_dist;
                    parent[v] = u;
                    pq_insert(pq, v, new_dist);
                }
            }
        }
    }
    printf("\n");
    
    if (dist[end] != INF) {
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
        p->total_cost = dist[end];
    }
    
    pq_free(pq);
    return p;
}


Path* astar(Graph* g, int start, int end) {
    Path* p = (Path*)malloc(sizeof(Path));
    p->size = 0;
    p->total_cost = 0;
    
    int g_score[MAX_NODES];
    int f_score[MAX_NODES];
    int parent[MAX_NODES];
    int closed[MAX_NODES];
    
    for (int i = 0; i < g->n; i++) {
        g_score[i] = INF;
        f_score[i] = INF;
        parent[i] = -1;
        closed[i] = 0;
    }
    g_score[start] = 0;
    f_score[start] = heuristic(g, start, end);
    
    PriorityQueue* open_set = pq_create();
    pq_insert(open_set, start, f_score[start]);
    
    printf("\n[A*] Processed nodes: ");
    
    while (!pq_is_empty(open_set)) {
        int current = pq_extract_min(open_set);
        
        if (current == end) {
            printf("%d (Target found)", current);
            break;
        }
        
        if (closed[current]) continue;
        
        closed[current] = 1;
        printf("%d ", current);
        
        for (int neighbor = 0; neighbor < g->n; neighbor++) {
            if (g->adj[current][neighbor] && !closed[neighbor]) {
                int tentative_g = g_score[current] + g->weights[current][neighbor];
                
                if (tentative_g < g_score[neighbor]) {
                    parent[neighbor] = current;
                    g_score[neighbor] = tentative_g;
                    f_score[neighbor] = g_score[neighbor] + heuristic(g, neighbor, end);
                    pq_insert(open_set, neighbor, f_score[neighbor]);
                }
            }
        }
    }
    printf("\n");
    
    if (g_score[end] != INF) {
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
        p->total_cost = g_score[end];
    }
    
    pq_free(open_set);
    return p;
}


int main() {
    printf("\n======== Dijkstra and A* ========\n");

    printf("\nUnweighted Graph\n");

    Graph* g1 = create_graph(7);
    
    add_edge(g1, 0, 1);
    add_edge(g1, 0, 2);
    add_edge(g1, 1, 3);
    add_edge(g1, 2, 3);
    add_edge(g1, 2, 4);
    add_edge(g1, 3, 5);
    add_edge(g1, 4, 5);
    add_edge(g1, 5, 6);
    
    set_node_position(g1, 0, 0, 0);
    set_node_position(g1, 1, 1, 1);
    set_node_position(g1, 2, 1, -1);
    set_node_position(g1, 3, 2, 0);
    set_node_position(g1, 4, 2, -2);
    set_node_position(g1, 5, 3, 0);
    set_node_position(g1, 6, 4, 0);
    
    printf("Finding path (0 -> 6)\n");
    
    Path* result1 = dijkstra(g1, 0, 6);
    printf("Dijkstra result: ");
    print_path(result1);
    free(result1);
    
    Path* result2 = astar(g1, 0, 6);
    printf("A* result: ");
    print_path(result2);
    free(result2);
    
    printf("\n");
    

    printf("\nWeighted Graph\n");

    Graph* g2 = create_graph(7);
    
    add_weighted_edge(g2, 0, 1, 7);
    add_weighted_edge(g2, 0, 2, 9);
    add_weighted_edge(g2, 0, 5, 14);
    add_weighted_edge(g2, 1, 2, 10);
    add_weighted_edge(g2, 1, 3, 15);
    add_weighted_edge(g2, 2, 3, 11);
    add_weighted_edge(g2, 2, 5, 2);
    add_weighted_edge(g2, 3, 4, 6);
    add_weighted_edge(g2, 4, 5, 9);
    add_weighted_edge(g2, 5, 4, 9);
    
    set_node_position(g2, 0, 0, 0);
    set_node_position(g2, 1, 1, 2);
    set_node_position(g2, 2, 2, 1);
    set_node_position(g2, 3, 3, 2);
    set_node_position(g2, 4, 4, 1);
    set_node_position(g2, 5, 2, -1);
    set_node_position(g2, 6, 5, 0);
    
    printf("Finding path (0 -> 4)\n");
    
    Path* result3 = dijkstra(g2, 0, 4);
    printf("Dijkstra result: ");
    print_path(result3);
    free(result3);
    
    Path* result4 = astar(g2, 0, 4);
    printf("A* result: ");
    print_path(result4);
    free(result4);
    
    printf("\n");

    free(g1);
    free(g2);

    return 0;
}