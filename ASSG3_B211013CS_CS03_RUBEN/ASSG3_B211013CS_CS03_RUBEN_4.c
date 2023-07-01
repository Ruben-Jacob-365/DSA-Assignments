#include <stdio.h>
#include <stdlib.h>

struct node
{
    int key;
    struct node *next;
};

typedef struct node *node;

typedef struct list
{
    node head;
} *list;

node create(int k)
{
    node new = (node)malloc(sizeof(struct node));
    new->key = k;
    new->next = NULL;
}

void insert(list l, int k)
{
    node n = create(k);
    node t = l->head;
    if (t == NULL)
    {
        l->head = n;
        return;
    }
    if (l->head->key > k)
    {
        n->next = l->head;
        l->head = n;
        return;
    }
    while (t->next != NULL && t->next->key < k)
        t = t->next;
    n->next = t->next;
    t->next = n;
}

int calculate(list l)
{
    int s = 0, c = 0;
    node t = l->head;
    while (t != NULL)
    {
        t = l->head;
        s = t->key + t->next->key;
        t = t->next->next;
        l->head = t;
        insert(l, s);
        c += s;
    }
    return c;
}

int main()
{
    int n, x, no;
    list l = (list)malloc(sizeof(struct list));
    l->head = NULL;
    scanf("%d", &n);
    no = n;
    if (n == 1)
    {
        scanf("%d", &x);
        printf("%d\n", x);
        return 0;
    }
    while (n--)
    {
        scanf("%d", &x);
        insert(l, x);
    }
    printf("%d\n", calculate(l));
}
