#include <stdio.h>
#include <stdlib.h>

typedef struct graph
{
    int n;
    int vertex[1000];
    int edge[1000][1000];
    char colour[1000];
    int pi[1000];
    int d[1000];
} *graph;

void bfs(graph g, int s)
{
    for (int i = 1; i < g->n; i++)
    {
        g->colour[i] = 'w';
        g->pi[i] = -1;
        g->d[i] = -1;
    }
    int q[1000];
    int head = 0, tail = 0;
    g->colour[s] = 'g';
    g->d[s] = 0;
    g->pi[s] = -1;
    q[tail++] = s;
    while (head != tail)
    {
        int u = q[head++];
        printf("%d ", u);
        for (int v = 0; v < g->n; v++)
        {
            if (g->edge[u][v] == 1 && g->colour[v] == 'w')
            {
                g->colour[v] = 'g';
                g->d[v] = g->d[u] + 1;
                g->pi[v] = u;
                q[tail++] = v;
            }
        }
        g->colour[u] = 'b';
    }
}

int main()
{
    int n;
    scanf("%d", &n);
    graph g = (graph)malloc(sizeof(struct graph));
    g->n = n;
    for (int i = 0; i < n; i++)
    {
        g->vertex[i] = 1;
        for (int j = 0; j < n; j++)
        {
            g->edge[i][j] = 0;
        }
    }
    char c;
    int v, e, no = 0;
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &v);
        g->vertex[v] = 1;
        for (int j = 0; j < n; j++)
        {
            scanf("%d%c", &e, &c);
            g->edge[v][e] = 1;
            if (c == '\n')
                break;
        }
    }
    bfs(g, 0);
}