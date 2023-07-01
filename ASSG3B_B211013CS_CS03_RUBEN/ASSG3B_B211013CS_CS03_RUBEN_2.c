#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int key;
    struct node *p;
    int rank;
} *node;

node arrn[10001] = {NULL};
node arru[10001] = {NULL};
node arrp[10001] = {NULL};
node arrb[10001] = {NULL};
int dn = 0, du = 0, dp = 0, db = 0;

void makeset(int x)
{
    node nn = (node)malloc(sizeof(struct node));
    node nu = (node)malloc(sizeof(struct node));
    node np = (node)malloc(sizeof(struct node));
    node nb = (node)malloc(sizeof(struct node));
    nn->key = x;
    nn->p = nn;
    nn->rank = 0;
    nu->key = x;
    nu->p = nu;
    nu->rank = 0;
    np->key = x;
    np->p = np;
    np->rank = 0;
    nb->key = x;
    nb->p = nb;
    nb->rank = 0;
    arrn[x] = nn;
    arru[x] = nu;
    arrp[x] = np;
    arrb[x] = nb;
}

node findsetnone(node x)
{
    if (x->p == x)
    {
        dn++;
        return x;
    }
    dn++;
    return findsetnone(x->p);
}

node findsetrank(node x)
{
    if (x->p == x)
    {
        du++;
        return x;
    }
    du++;
    return findsetrank(x->p);
}

node findsetpath(node x)
{
    if (x->p == x)
    {
        dp++;
        return x->p;
    }
    dp++;
    x->p = findsetpath(x->p);
    return x->p;
}

node findsetboth(node x)
{
    if (x->p == x)
    {
        db++;
        return x->p;
    }
    db++;
    x->p = findsetboth(x->p);
    return x->p;
}

node unionnone(int x, int y)
{
    node xt = arrn[x];
    node yt = arrn[y];
    if (xt == NULL || yt == NULL)
        return NULL;
    node yr = findsetnone(yt);
    node xr = findsetnone(xt);
    yr->p = xr;
    return xr;
}

node unionpath(int x, int y)
{
    node xt = arrp[x];
    node yt = arrp[y];
    node yr = findsetpath(yt);
    node xr = findsetpath(xt);
    yr->p = xr;
    return xr;
}

void linkrank(node x, node y)
{
    if (x->rank > y->rank)
        y->p = x;
    else if (y->rank > x->rank)
    {
        x->p = y;
    }
    else if (x->rank == y->rank)
    {
        y->p = x;
        x->rank++;
    }
}

node unionrank(int x, int y)
{
    node xt = arru[x];
    node yt = arru[y];
    node xr = findsetrank(xt);
    node yr = findsetrank(yt);
    linkrank(xr, yr);
    return (xr->p);
}

node unionboth(int x, int y)
{
    node xt = arrb[x];
    node yt = arrb[y];
    node xr = findsetboth(xt);
    node yr = findsetboth(yt);
    linkrank(xr, yr);
    return (xr->p);
}

int main()
{
    char c;
    int x, y;
    while (c != 's')
    {
        c = getchar();
        switch (c)
        {
        case 'm':
            scanf("%d", &x);
            if (arrn[x] == NULL)
            {
                makeset(x);
                printf("%d\n", x);
            }
            else
                printf("%d\n", -1);
            break;
        case 'f':
            scanf("%d", &x);
            node tn = arrn[x];
            node tu = arru[x];
            node tp = arrp[x];
            node tb = arrb[x];
            if (tu == NULL)
                printf("-1\n");
            else
                printf("%d %d %d %d\n", findsetnone(tn)->key, findsetrank(tu)->key, findsetpath(tp)->key, findsetboth(tb)->key);
            break;
        case 'u':
            scanf("%d %d", &x, &y);
            node n = unionnone(x, y);
            if (n == NULL)
            {
                printf("-1\n");
                break;
            }
            node u = unionrank(x, y);
            node p = unionpath(x, y);
            node b = unionboth(x, y);
            printf("%d %d %d %d\n", n->key, u->key, p->key, b->key);
            break;
        }
    }
    printf("%d %d %d %d\n", dn, du, dp, db);
}
