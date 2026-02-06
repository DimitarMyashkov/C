#include <stdio.h>

#define MAX 100
#define INF 1000000

void primMST(int graph[MAX][MAX], int n) {
    int selected[MAX];
    int i, j;

    for (i = 0; i < n; i++)
        selected[i] = 0;

    selected[0] = 1;

    int edges = 0;

    printf("edges in MST:\n");

    while (edges < n - 1) {
        int min = INF;
        int x = -1, y = -1;

        for (i = 0; i < n; i++) {
            if (selected[i]) {
                for (j = 0; j < n; j++) {
                    if (!selected[j] && graph[i][j] != 0) {
                        if (graph[i][j] < min) {
                            min = graph[i][j];
                            x = i;
                            y = j;
                        }
                    }
                }
            }
        }

        printf("%d - %d : %d\n", x, y, graph[x][y]);

        selected[y] = 1;
        edges++;
    }
}

int main() {
    int graph[MAX][MAX] = {
        {0, 2, 0, 6, 0},
        {2, 0, 3, 8, 5},
        {0, 3, 0, 0, 7},
        {6, 8, 0, 0, 9},
        {0, 5, 7, 9, 0}
    };

    int n = 5;

    primMST(graph, n);

    return 0;
}
