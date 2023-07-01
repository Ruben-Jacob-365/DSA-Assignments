#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int key;
    int ht;
    int no_of_elements;
    struct node *left;
    struct node *right;
} *node;

typedef struct avltree
{
    node root;
}
    *tree;

node nilnode()
{
    node n = (node)malloc(sizeof(struct node));
    n->ht = -1;
    n->no_of_elements = -1;
    n->left = NULL;
    n->right = NULL;
    return n;
}

node create(int k)
{
    node new = (node)malloc(sizeof(struct node));
    new->ht = 0;
    new->left = nilnode();
    new->right = nilnode();
    new->key = k;
    new->no_of_elements = 1;
    return new;
}

int max(int a, int b)
{
    return (a > b) ? a : b;
}

int nodes(node t)
{
    if (t->ht == -1)
        return 0;
    return 1 + nodes(t->left) + nodes(t->right);
}

node leftrotate(node x)
{
    node a = x->right;
    node b = a->left;
    x->right = b;
    a->left = x;
    a->ht = max(a->left->ht, a->right->ht) + 1;
    x->ht = max(x->right->ht, x->left->ht) + 1;
    a->no_of_elements = nodes(a);
    x->no_of_elements = nodes(x);
    return a;
}

node rightrotate(node x)
{
    node a = x->left;
    node b = a->right;
    x->left = b;
    a->right = x;
    a->ht = max(a->left->ht, a->right->ht) + 1;
    x->ht = max(x->right->ht, x->left->ht) + 1;
    a->no_of_elements = nodes(a);
    x->no_of_elements = nodes(x);
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
        t->no_of_elements = nodes(t);
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
        t->no_of_elements = nodes(t);
        return t;
    }
}

void insert(tree t, int k)
{
    node n = create(k);
    t->root = inserts(t->root, n);
}

node treemin(node t)
{
    if (t->ht == -1)
        return nilnode();
    while (t->left->ht != -1)
        t = t->left;
    return t;
}

node successor(node t, node x)
{
    if (t->ht == -1)
        return nilnode();
    else if (t->key == x->key)
        return treemin(t->right);
    else if (x->key > t->key)
        return successor(t->right, x);
    else
    {
        if (successor(t->left, x)->ht == -1)
            return t;
        else
            return successor(t->left, x);
    }
}

int getMedian(node t)
{
    node x = treemin(t);
    int n = t->no_of_elements, k;
    if (n % 2 == 0)
        k = n / 2;
    else
        k = (n + 1) / 2;
    while (--k)
    {
        x = successor(t, x);
    }
    return x->key;
}

node search(node t, int k)
{
    if (t->ht == -1 || t->key == k)
        return t;
    else if (k < t->key)
        return search(t->left, k);
    else
        return search(t->right, k);
}

void print(node t)
{
    if (t->ht != -1)
    {
        printf("%d-%d ", t->key, t->no_of_elements);
        print(t->left);
        print(t->right);
    }
}

int main()
{
    tree t = (tree)malloc(sizeof(struct avltree));
    t->root = nilnode();
    char ch;
    int k;
    while (ch != 't')
    {
        ch = getchar();
        switch (ch)
        {
        case 'i':
            scanf("%d", &k);
            insert(t, k);
            break;
        case 'p':
            print(t->root);
            printf("\n");
            break;
        case 'g':
            k = getMedian(t->root);
            printf("%d\n", k);
            break;
        case 'r':
            scanf("%d", &k);
            node n = search(t->root, k);
            printf("%d\n", successor(t->root, n)->key);
            break;
        }
    }
}
