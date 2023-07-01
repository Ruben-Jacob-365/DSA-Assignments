#include <stdio.h>
#include <stdlib.h>

typedef struct edge
{
    int u;
    int v;
    int weight;
} edge;

typedef struct graphkrus
{
    int novert;
    int noedge;
    edge e[1000];
} *graphkrus;

typedef struct graphprim
{
    int nov;
    int weight[1000][1000];
} *graphprim;

typedef struct node
{
    int key;
    struct node *p;
    int degree;
} *node;

typedef struct nodeprim
{
    int vertex;
    int key;
} *nodeprim;

typedef struct heap
{
    int size;
    nodeprim arr[1000];
} *heap;

nodeprim create(int v, int k)
{
    nodeprim n = (nodeprim)malloc(sizeof(struct nodeprim));
    n->key = k;
    n->vertex = v;
    return n;
}

void insert(heap h, nodeprim k)
{
    h->size++;
    int i = h->size - 1;
    h->arr[i] = k;
    while (i > 0 && h->arr[(i - 1) / 2]->key > h->arr[i]->key)
    {
        nodeprim t = h->arr[(i - 1) / 2];
        h->arr[(i - 1) / 2] = h->arr[i];
        h->arr[i] = t;
        i = (i - 1) / 2;
    }
}

void heapify(heap h, int i)
{
    int l = 2 * i + 1, r = 2 * i + 2;
    int min = i;
    if (l < h->size && h->arr[l]->key < h->arr[i]->key)
        min = l;
    if (r < h->size && h->arr[r]->key < h->arr[min]->key)
        min = r;
    if (min != i)
    {
        nodeprim t = h->arr[min];
        h->arr[min] = h->arr[i];
        h->arr[i] = t;
        heapify(h, min);
    }
}

nodeprim extractmin(heap h)
{
    nodeprim min = h->arr[0];
    h->arr[0] = h->arr[h->size - 1];
    h->size--;
    heapify(h, 0);
    return min;
}

int getmin(heap h)
{
    return h->arr[0]->key;
}

node set[1001] = {NULL};

void makeset(int x)
{
    node n = (node)malloc(sizeof(struct node));
    n->key = x;
    n->degree = 0;
    n->p = n;
    set[x] = n;
}

node findset(node x)
{
    if (x->p == x)
        return x->p;
    x->p = findset(x->p);
    return x->p;
}

void link(node x, node y)
{
    if (y->degree > x->degree)
        x->p = y;
    else
    {
        y->p = x;
        if (x->degree == y->degree)
            x->degree++;
    }
}

void unionset(node x, node y)
{
    link(findset(x), findset(y));
}

void swap(edge *x, edge *y)
{
    int t = x->weight;
    x->weight = y->weight;
    y->weight = t;
    int u = x->u;
    x->u = y->u;
    y->u = u;
    int v = x->v;
    x->v = y->v;
    y->v = v;
}

int partition(edge a[], int p, int r)
{
    int i = p, pivot = a[r].weight, j = p;
    for (i = p; i < r; i++)
    {
        if (a[i].weight < pivot)
        {
            swap(&a[i], &a[j]);
            j++;
        }
    }
    swap(&a[j], &a[r]);
    return j;
}

void sort(edge a[], int p, int r)
{
    if (p < r)
    {
        int q = partition(a, p, r);
        sort(a, p, q - 1);
        sort(a, q + 1, r);
    }
}

int kruskal(graphkrus g)
{
    int a = 0;
    for (int i = 0; i < g->novert; i++)
    {
        makeset(i);
    }
    sort(g->e, 0, g->noedge - 1);
    for (int i = 0; i < g->noedge; i++)
    {
        node setu = set[g->e[i].u];
        node setv = set[g->e[i].v];
        if (findset(setu) != findset(setv))
        {
            a += g->e[i].weight;
            unionset(setu, setv);
        }
    }
    return a;
}

int allmarked(int a[], int n)
{
    int m = 0;
    for (int i = 0; i < n; i++)
    {
        if (a[i] == 1)
            m++;
    }
    if (m == n)
        return 1;
    else
        return 0;
}

int prims(graphprim gp)
{
    int parent[1000];
    int key[1000];
    int marked[1000];
    int a = 0;
    heap h = (heap)malloc(sizeof(struct heap));
    h->size = 0;
    for (int i = 0; i < gp->nov; i++)
    {
        marked[i] = 0;
        parent[i] = -1;
        key[i] = 100000;
    }
    key[0] = 0;
    nodeprim n = create(0, 0);
    insert(h, n);
    while (!allmarked(marked, gp->nov))
    {
        nodeprim n = extractmin(h);
        int u = n->vertex;
        a += n->key;
        marked[u] = 1;
        for (int v = 0; v < gp->nov; v++)
        {
            if (gp->weight[u][v] != 100000 && marked[v] == 0 && gp->weight[u][v] < key[v])
            {

                key[v] = gp->weight[u][v];
                parent[v] = u;
                nodeprim t = create(v, key[v]);
                insert(h, t);
            }
        }
    }
    return a;
}

int main()
{
    int n, u, v;
    graphkrus gk = (graphkrus)malloc(sizeof(struct graphkrus));
    graphprim gp = (graphprim)malloc(sizeof(struct graphprim));
    gk->noedge = 0;
    for (int i = 0; i < 1000; i++)
    {
        gk->e[i].u = -1;
        gk->e[i].v = -1;
        gk->e[i].weight = -1;
    }
    char c, ch;
    scanf("%c", &ch);
    scanf("%d", &n);
    gk->novert = n;
    gp->nov = n;
    int k = 0;
    int edge[20001] = {0};
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            gp->weight[i][j] = 100000;
        }
    }
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &u);
        for (int j = 0; j < n; j++)
        {
            scanf("%d%c", &v, &c);
            if (u < v)
            {
                gk->e[k].u = u;
                gk->e[k].v = v;
                k++;
            }
            gp->weight[u][v] = -100000;
            if (c == '\n')
                break;
        }
    }
    gk->noedge = k;
    k = 0;
    int w;
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &u);
        for (v = 0; v < n; v++)
        {
            if (gp->weight[u][v] == -100000)
                break;
        }
        for (int j = 0; j < n; j++)
        {
            scanf("%d%c", &w, &c);
            if (!edge[w + 10000])
            {
                edge[w + 10000] = 1;
                gk->e[k].weight = w;
                k++;
            }
            gp->weight[u][v] = w;
            while (v < n)
            {
                if (gp->weight[u][v] == -100000)
                    break;
                v++;
            }
            if (c == '\n')
                break;
        }
    }
    if (ch == 'a')
    {
        printf("%d\n", kruskal(gk));
    }
    else if (ch == 'b')
    {
        printf("%d\n", prims(gp));
    }
}
/*
7
0 1 5
1 0 2 6
2 1 3
3 2 4 6
4 3 5 6
5 0 4
6 1 3 4
0 28 10
1 28 16 14
2 16 12
3 12 22 18
4 22 25 24
5 10 25
6 14 18 24
*/