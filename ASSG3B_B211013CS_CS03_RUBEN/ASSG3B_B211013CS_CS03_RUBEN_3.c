#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int key;
    int rank;
    struct node *p;
} *node;

node arr[1001] = {NULL};

void makeset(int x)
{
    node n = (node)malloc(sizeof(struct node));
    n->key = x;
    n->p = n;
    n->rank = 0;
    arr[x] = n;
}

node findset(node x)
{
    if (x->p != x)
    {
        x->p = findset(x->p);
    }
    return x->p;
}

void link(node x, node y)
{
    if (x->rank > y->rank)
        y->p = x;
    else if (y->rank > x->rank)
        x->p = y;
    else
    {
        y->p = x;
        x->rank++;
    }
}

void unionset(node x, node y)
{
    node xr = findset(x);
    node yr = findset(y);
    link(xr, yr);
}

int main()
{
    char c;
    int x, y;
    int teams = 0, team[1001], count = 0;

    while (c != 'e')
    {
        c = getchar();
        switch (c)
        {
        case 't':
            scanf("%d %d", &x, &y);
            if (arr[x] == NULL && arr[y] == NULL)
                teams++;
            if (arr[x] == NULL)
                makeset(x);
            if (arr[y] == NULL)
                makeset(y);
            unionset(arr[x], arr[y]);
            int xk = findset(arr[x])->key;
            int yk = findset(arr[y])->key;
            team[xk] = xk;
            team[yk] = xk;
            break;
        case 'T':
            printf("%d\n", teams);
            break;
        case 'd':
            if (teams == 1)
                printf("-1\n");
            else
            {
                count = 0;
                for (int i = 0; i < 1002; i++)
                {
                    if (arr[i] != NULL)
                    {
                        for (int j = i + 1; j < 1002; j++)
                        {
                            if (arr[j] != NULL && findset(arr[i]) != findset(arr[j]))
                                count++;
                        }
                    }
                }
                printf("%d\n", count);
            }
            break;
        case 'v':
            scanf("%d %d", &x, &y);
            if (arr[x] == NULL || arr[y] == NULL || x > y)
                printf("%d\n", -1);
            else
            {
                if (findset(arr[x]) != findset(arr[y]))
                    printf("1\n");
                else
                    printf("-1\n");
            }
            break;
        }
    }
}
