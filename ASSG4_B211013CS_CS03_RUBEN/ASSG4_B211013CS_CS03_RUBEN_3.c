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
    int f[1000];
} *graph;

int time = 0;

void dfsvisit(graph g, int u)
{
    time = time + 1;
    g->d[u] = time;
    g->colour[u] = 'g';
    printf("%d ", u);
    for (int v = 0; v < g->n; v++)
    {
        if (g->edge[u][v] && g->colour[v] == 'w')
        {
            g->pi[v] = u;
            dfsvisit(g, v);
        }
    }
    g->colour[u] = 'b';
    time = time + 1;
    g->f[u] = time;
}

void dfs(graph g)
{
    for (int i = 0; i < g->n; i++)
    {
        g->colour[i] = 'w';
        g->pi[i] = -1;
    }
    for (int u = 0; u < g->n; u++)
    {
        if (g->colour[u] == 'w')
            dfsvisit(g, u);
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
    dfs(g);
}