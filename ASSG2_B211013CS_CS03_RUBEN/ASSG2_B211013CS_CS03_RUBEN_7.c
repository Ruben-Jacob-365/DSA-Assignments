#include <stdio.h>
#include <stdlib.h>
typedef struct node
{
    int key;
    int ht;
    struct node *left;
    struct node *right;
} *node;

typedef struct avltree
{
    node root;
} *tree;

node nilnode()
{
    node new = (node)malloc(sizeof(struct node));
    new->ht = -1;
    new->left = NULL;
    new->right = NULL;
    return new;
}

node create(int k)
{
    node new = (node)malloc(sizeof(struct node));
    new->key = k;
    new->left = nilnode();
    new->right = nilnode();
    new->ht = 0;
    return new;
}

int max(int a, int b)
{
    return (a > b) ? a : b;
}

node leftrotate(node x)
{
    node a = x->right;
    node b = a->left;
    x->right = b;
    a->left = x;
    a->ht = max(a->left->ht, a->right->ht) + 1;
    x->ht = max(x->left->ht, x->right->ht) + 1;
    return a;
}

node rightrotate(node x)
{
    node a = x->left;
    node b = a->right;
    x->left = b;
    a->right = x;
    a->ht = max(a->left->ht, a->right->ht) + 1;
    x->ht = max(x->left->ht, x->right->ht) + 1;
    return a;
}

node inserts(node t, node x)
{
    if (t->ht == -1)
        return x;
    if (x->key < t->key)
    {
        t->left = inserts(t->left, x);
        if (t->left->ht - t->right->ht > 1)
        {
            if (t->left->right->ht > t->left->left->ht)
                t->left = leftrotate(t->left);
            return rightrotate(t);
        }
        t->ht = max(t->left->ht, t->right->ht) + 1;
        return t;
    }
    else
    {
        t->right = inserts(t->right, x);
        if (t->right->ht - t->left->ht > 1)
        {
            if (t->right->left->ht > t->right->right->ht)
                t->right = rightrotate(t->right);
            return leftrotate(t);
        }
        t->ht = max(t->left->ht, t->right->ht) + 1;
        return t;
    }
}

int countnodes(node t, int k)
{
    if (t->ht == -1)
        return 0;
    if (t->key > k)
        return 1 + countnodes(t->right, k) + countnodes(t->left, k);
    return 0 + countnodes(t->left, k) + countnodes(t->right, k);
}

void printnodes(node t, int k)
{
    if (t->ht != -1)
    {
        printnodes(t->left, k);
        if (t->key > k)
            printf("%d ", t->key);
        printnodes(t->right, k);
    }
}

void countNodesGreaterThanK(node t, int k)
{
    int c = countnodes(t, k);
    printf("%d\n", c);
    if (c)
    {
        printnodes(t, k);
        printf("\n");
    }
}

void insert(tree t, int k)
{
    node n = create(k);
    t->root = inserts(t->root, n);
}

int main()
{
    tree t = (tree)malloc(sizeof(struct avltree));
    t->root = nilnode();
    char ch;
    int k, c;
    while (ch != 'e')
    {
        ch = getchar();
        switch (ch)
        {
        case 'i':
            scanf("%d", &k);
            insert(t, k);
            break;
        case 'c':
            scanf("%d", &k);
            countNodesGreaterThanK(t->root, k);
            break;
        }
    }
}
