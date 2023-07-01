#include <stdio.h>
#include <stdlib.h>

struct node
{
    int degree;
    int key;
    struct node *sibling;
    struct node *child;
    struct node *parent;
};

typedef struct node *node;

node makeheap()
{
    node h = (node)malloc(sizeof(struct node));
    h = NULL;
    return h;
}

node create(int k)
{
    node x = (node)malloc(sizeof(struct node));
    x->child = NULL;
    x->degree = 0;
    x->key = k;
    x->parent = NULL;
    x->sibling = NULL;
    return x;
}

void print(node h)
{
    while (h != NULL)
    {
        printf("%d ", h->key);
        h = h->sibling;
    }
}

node merge(node h1, node h2)
{
    node t1 = h1;
    node t2 = h2;
    node p1 = h1;
    node p2 = h2;
    if (h1 == NULL)
        return h2;
    if (h2 == NULL)
        return h1;
    while (t1 != NULL && t2 != NULL)
    {
        if (t1->degree == t2->degree)
        {
            p1 = t1;
            t1 = t1->sibling;
            p2 = t2;
            t2 = t2->sibling;
            p1->sibling = p2;
            p2->sibling = t1;
            t1 = p2;
        }
        else if (t1->degree < t2->degree)
        {
            p1 = t1;
            t1 = t1->sibling;
        }
        else if (t1->degree > t2->degree)
        {
            if (p1 == h1)
            {
                h1 = t2;
                p2 = t2;
                t2 = t2->sibling;
                p2->sibling = t1;
            }
            else
            {
                p2 = t2;
                t2 = t2->sibling;
                p1->sibling = p2;
                p2->sibling = t1;
            }
        }
        if (t1 == NULL)
            p1->sibling = t2;
    }
    h2 = NULL;
    return h1;
}

void link(struct node *h1, struct node *h2)
{
    h2->parent = h1;
    h2->sibling = h1->child;
    h1->child = h2;
    h1->degree += 1;
}

node heapunion(node h1, node h2)
{
    struct node *h = makeheap();
    h = merge(h1, h2);
    struct node *prev = NULL;
    struct node *current = NULL;
    struct node *next = NULL;
    h1 = NULL;
    if (h == NULL)
    {
        return h;
    }
    current = h;
    next = current->sibling;
    while (next != NULL)
    {
        if ((current->degree != next->degree) || (next->sibling != NULL && next->degree == next->sibling->degree))
        {
            prev = current;
            current = next;
        }
        else if (current->key < next->key)
        {
            current->sibling = next->sibling;
            link(current, next);
        }
        else if (prev == NULL)
        {
            h = next;
            link(next, current);
            current = next;
        }
        else
        {
            prev->sibling = next;
            link(next, current);
            current = next;
        }
        next = next->sibling;
    }
    return h;
}

node insert(node h, int k)
{
    node h1 = create(k);
    h = heapunion(h, h1);
    return h;
}

node findmin(node h)
{
    node t = h;
    node minnode;
    int min = 10000000;
    while (t != NULL)
    {
        if (t->key < min)
        {
            min = t->key;
            minnode = t;
        }
        t = t->sibling;
    }
    return minnode;
}

node search(node h, int k)
{
    struct node *p = NULL;
    if (h->key == k)
    {
        p = h;
        return p;
    }
    if ((h->child != NULL) && (p == NULL))
    {
        p = search(h->child, k);
    }
    if ((h->sibling != NULL) && (p == NULL))
    {
        p = search(h->sibling, k);
    }
    return p;
}

node decreasekey(node h, int y, int z)
{
    node t = search(h, y);
    t->key = z;
    node p = t->parent;
    while (p != NULL && p->key > t->key)
    {
        int x = t->key;
        t->key = p->key;
        p->key = x;
        t = p;
        p = t->parent;
    }
    return h;
}

node extractmin(node h)
{
    node t = findmin(h);
    node curr = t->child;
    node prev = NULL;
    node next = NULL;
    if (h == t && t->sibling == NULL)
    {
        h = t->child;
        while (curr != NULL)
        {
            next = curr->sibling;
            curr->sibling = prev;
            prev = curr;
            curr = next;
        }
        h = prev;
        while (prev != NULL)
        {
            prev->parent = NULL;
            prev = prev->sibling;
        }
        return h;
    }
    if (h == t && t->sibling != NULL)
    {
        h = t->sibling;
        while (curr != NULL)
        {
            next = curr->sibling;
            curr->sibling = prev;
            prev = curr;
            curr = next;
        }
        node htemp = makeheap();
        htemp = prev;
        while (prev != NULL)
        {
            prev->parent = NULL;
            prev = prev->sibling;
        }
        h = heapunion(h, htemp);
        return h;
    }
    while (curr != NULL)
    {
        next = curr->sibling;
        curr->sibling = prev;
        prev = curr;
        curr = next;
    }
    node htemp = makeheap();
    htemp = prev;
    while (prev != NULL)
    {
        prev->parent = NULL;
        prev = prev->sibling;
    }
    prev = h;
    while (prev->sibling != t)
    {
        prev = prev->sibling;
    }
    prev->sibling = t->sibling;
    t->sibling = NULL;
    t->child = NULL;
    h = heapunion(h, htemp);
    return h;
}

node delete(node h, int k)
{
    h = decreasekey(h, k, -1000000);
    h = extractmin(h);
    return h;
}

int main()
{
    node h1 = makeheap();
    node h2 = makeheap();
    char c;
    int k, x, r, n, y, z;
    while (c != 'e')
    {
        c = getchar();
        switch (c)
        {
        case 'i':
            scanf("%d", &n);
            h1 = insert(h1, n);
            break;
        case 'j':
            scanf("%d", &n);
            h2 = insert(h2, n);
            break;
        case 'd':
            scanf("%d", &x);
            if (search(h1, x) == NULL)
            {
                printf("-1\n");
                break;
            }
            else
            {
                h1 = delete (h1, x);
                printf("%d\n", x);
            }
            break;
        case 'p':
            scanf("%d", &k);
            if (k == 1)
                print(h1);
            else
                print(h2);
            printf("\n");
            break;
        case 'm':
            printf("%d\n", findmin(h1)->key);
            break;
        case 'x':
            printf("%d\n", findmin(h1)->key);
            h1 = extractmin(h1);
            break;
        case 'r':
            scanf("%d %d", &y, &z);
            node t = search(h1, y);
            if (t == NULL || z > y)
            {
                printf("%d\n", -1);
                break;
            }
            decreasekey(h1, y, z);
            printf("%d\n", z);
            break;
        case 'u':
            h1 = heapunion(h2, h1);
            print(h1);
            h2 = NULL;
            printf("\n");
            break;
        }
    }
}
