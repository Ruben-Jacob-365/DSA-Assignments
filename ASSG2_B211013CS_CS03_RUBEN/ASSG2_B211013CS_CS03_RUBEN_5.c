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
} *avltree;

node nilnode()
{
    node n = (node)malloc(sizeof(struct node));
    n->left = NULL;
    n->right = NULL;
    n->key = -1;
    n->ht = -1;
    return n;
}

node create(int k)
{
    node new = (node)malloc(sizeof(struct node));
    new->key = k;
    new->ht = 0;
    new->left = nilnode();
    new->right = nilnode();
    return new;
}

int max(int a, int b)
{
    return (a > b) ? a : b;
}

node rightrotate(node t)
{
    node a = t->left;
    node b = a->right;
    a->right = t;
    t->left = b;
    t->ht = max(t->left->ht, t->right->ht) + 1;
    a->ht = max(a->left->ht, a->right->ht) + 1;
    return a;
}

node leftrotate(node t)
{
    node a = t->right;
    node b = a->left;
    a->left = t;
    t->right = b;
    t->ht = max(t->left->ht, t->right->ht) + 1;
    a->ht = max(a->left->ht, a->right->ht) + 1;
    return a;
}

node inserts(node t, node n)
{
    if (t->ht == -1)
        return n;
    if (n->key < t->key)
    {
        t->left = inserts(t->left, n);
        if (t->left->ht - t->right->ht > 1)
        {
            if (t->left->left->ht < t->left->right->ht)
                t->left = leftrotate(t->left);
            return rightrotate(t);
        }
        else
        {
            t->ht = max(t->left->ht, t->right->ht) + 1;
            return t;
        }
    }
    else
    {
        t->right = inserts(t->right, n);
        if (t->right->ht - t->left->ht > 1)
        {
            if (t->right->left->ht > t->right->right->ht)
                t->right = rightrotate(t->right);
            return leftrotate(t);
        }
        else
        {
            t->ht = max(t->left->ht, t->right->ht) + 1;
            return t;
        }
    }
}

void insert(avltree t, int k)
{
    node n = create(k);
    t->root = inserts(t->root, n);
}

node treemax(node t)
{
    if (t->ht == -1)
        return nilnode();
    while (t->right->ht != -1)
        t = t->right;
    return t;
}

node predecessor(node t, node x)
{
    if (t->ht == -1)
        return nilnode();
    else if (t->key == x->key)
        return treemax(t->left);
    else if (x->key < t->key)
        return predecessor(t->left, x);
    else
    {
        if (predecessor(t->right, x)->ht == -1)
            return t;
        else
            return predecessor(t->right, x);
    }
}

node delete(node t, node x)
{
    if (x->key > t->key)
    {
        t->right = delete (t->right, x);
        if (t->left->ht - t->right->ht > 1)
        {
            if (t->left->right->ht > t->left->left->ht)
                t->left = leftrotate(t->left);
            return rightrotate(t);
        }
        else
        {
            t->ht = max(t->left->ht, t->right->ht) + 1;
            return t;
        }
    }
    else if (x->key < t->key)
    {
        t->left = delete (t->left, x);
        if (t->right->ht - t->left->ht > 1)
        {
            if (t->right->left->ht > t->right->right->ht)
                t->right = rightrotate(t->right);
            return leftrotate(t);
        }
        else
        {
            t->ht = max(t->left->ht, t->right->ht) + 1;
            return t;
        }
    }
    else
    {
        if (t->left->ht == -1 && t->right->ht == -1)
            return nilnode();
        else if (t->left->ht == -1)
            return t->right;
        else if (t->right->ht == -1)
            return t->left;
        else
        {
            node a = predecessor(t, t);
            node b = t;
            t = delete (t, a);
            b->key = a->key;
            t->ht = max(t->left->ht, t->right->ht) + 1;
            a->ht = max(a->left->ht, a->right->ht) + 1;
            return t;
        }
    }
}

node searchs(node t, int k)
{
    if (t->ht == -1 || t->key == k)
        return t;
    else if (k < t->key)
        return searchs(t->left, k);
    else
        return searchs(t->right, k);
}

node search(avltree t, int k)
{
    return searchs(t->root, k);
}

void deletenode(avltree t, int k)
{
    node n = search(t, k);
    if (n->ht == -1)
        printf("FALSE\n");
    else
    {
        t->root = delete (t->root, n);
        printf("%d\n", k);
    }
}

void print(node t)
{
    if (t->ht != -1)
    {
        printf("%d ", t->key);
        printf("( ");
        print(t->left);
        printf(") ( ");
        print(t->right);
        printf(") ");
    }
}

void printtree(avltree t)
{
    printf("( ");
    print(t->root);
    printf(")\n");
}

void getbalance(avltree t, int k)
{
    node x = search(t, k);
    if (x->ht != -1)
        printf("%d\n", x->left->ht - x->right->ht);
    else
        printf("FALSE\n");
    return;
}

int main()
{
    avltree tree = (avltree)malloc(sizeof(struct avltree));
    tree->root = nilnode();
    char ch;
    int k;
    while (ch != 'e')
    {
        ch = getchar();
        switch (ch)
        {
        case 'i':
            scanf("%d", &k);
            insert(tree, k);
            break;
        case 'd':
            scanf("%d", &k);
            deletenode(tree, k);
            break;
        case 's':
            scanf("%d", &k);
            node x = search(tree, k);
            if (x->ht != -1)
                printf("TRUE\n");
            else
                printf("FALSE\n");
            break;
        case 'b':
            scanf("%d", &k);
            getbalance(tree, k);
            break;
        case 'r':
            scanf("%d", &k);
            node s = search(tree, k);
            printf("%d\n", predecessor(tree->root, s)->key);
            break;
        case 'p':
            printtree(tree);
            break;
        }
    }
}