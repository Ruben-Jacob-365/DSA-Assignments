#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100000

typedef struct graph
{
    int vertices;
    int adj[1000][1000];
} *graph;

int mindist(int dist[], int marked[], int n)
{
    int min = MAX, minu;
    for (int u = 0; u < n; u++)
    {
        if (marked[u] == 0 && dist[u] <= min)
        {
            min = dist[u];
            minu = u;
        }
    }
    return minu;
}

void dijkstra(graph g, int st, int en)
{
    int n = g->vertices;
    int marked[n], dist[n];
    for (int i = 0; i < n; i++)
    {
        marked[i] = 0;
        dist[i] = MAX;
    }
    dist[st] = 0;
    int u, v;
    for (int i = 0; i < n; i++)
    {
        u = mindist(dist, marked, g->vertices);
        marked[u] = 1;
        for (v = 0; v < n; v++)
        {
            if (marked[v] == 0 && g->adj[u][v] != MAX && dist[u] + g->adj[u][v] < dist[v])
            {
                dist[v] = dist[u] + g->adj[u][v];
            }
        }
    }
    if (en == -1)
    {
        for (int i = 0; i < n; i++)
        {
            if (dist[i] != MAX)
                printf("%d ", dist[i]);
            else
                printf("INF ");
        }
        printf("\n");
    }
    else
    {
        if (dist[en] != MAX)
            printf("%d\n", dist[en]);
        else
            printf("UNREACHABLE\n");
    }
}

int main()
{
    int n;
    scanf("%d", &n);
    graph g = (graph)malloc(sizeof(struct graph));
    g->vertices = n;
    int u, v, w;
    char c;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            g->adj[i][j] = MAX;
        }
    }
    for (int i = 0; i < n; i++)
    {
        scanf("%d%c", &u, &c);
        if (c == '\n')
            continue;
        for (int j = 0; j < n; j++)
        {
            scanf("%d%c", &v, &c);
            g->adj[u][v] = -1;
            if (c == '\n')
                break;
        }
    }
    for (int i = 0; i < n; i++)
    {
        scanf("%d%c", &u, &c);
        if (c == '\n')
            continue;
        for (v = 0; v < n; v++)
            if (g->adj[u][v] == -1)
                break;
        for (int j = 0; j < n; j++)
        {
            scanf("%d%c", &w, &c);
            g->adj[u][v] = w;
            while (v < n)
            {
                if (g->adj[u][v] == -1)
                    break;
                v++;
            }
            if (c == '\n')
                break;
        }
    }
    char ch[1000];
    while (strcmp(ch, "stop") != 0)
    {
        scanf("%s", ch);
        if (strcmp(ch, "apsp") == 0)
        {
            scanf("%d", &u);
            dijkstra(g, u, -1);
        }
        else if (strcmp(ch, "sssp") == 0)
        {
            scanf("%d %d", &u, &v);
            dijkstra(g, u, v);
        }
    }
}
