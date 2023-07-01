#include <stdio.h>
#include <stdlib.h>
struct node
{
    int key;
    struct node *left;
    struct node *right;
    struct node *p;
};
typedef struct node *node;
struct tree
{
    node root;
};
typedef struct tree *tree;

node createnode(int k)
{
    node new = (node)malloc(sizeof(struct node));
    new->key = k;
    new->left = NULL;
    new->right = NULL;
    new->p = NULL;
    return new;
}

void insert(tree t, node n)
{
    node x = t->root, y = NULL;
    while (x != NULL)
    {
        y = x;
        if (n->key < x->key)
            x = x->left;
        else
            x = x->right;
    }
    n->p = y;
    if (y == NULL)
        t->root = n;
    else if (n->key < y->key)
        y->left = n;
    else
        y->right = n;
}

void transplant(tree t, node x, node y)
{
    if (x->p == NULL)
        t->root = y;
    else if (x == x->p->left)
        x->p->left = y;
    else
        x->p->right = y;
    if (y != NULL)
        y->p = x->p;
}

node treemin(node t)
{
    while (t->left != NULL)
        t = t->left;
    return t;
}

node treemax(node t)
{
    while (t->right != NULL)
        t = t->right;
    return t;
}

void delete(tree t, node x)
{
    if (x->left == NULL)
        transplant(t, x, x->right);
    else if (x->right == NULL)
        transplant(t, x, x->left);
    else
    {
        node y = treemin(x->right);
        if (y->p != x)
        {
            transplant(t, y, y->right);
            y->right = x->right;
            y->right->p = y;
        }
        transplant(t, x, y);
        y->left = x->left;
        y->left->p = y;
    }
}

node searchs(node t, int k)
{
    if (t == NULL || t->key == k)
        return t;
    if (k < t->key)
        return searchs(t->left, k);
    else
        return searchs(t->right, k);
}

node search(tree t, int k)
{
    return searchs(t->root, k);
}

int minvalue(tree t)
{
    node x = t->root;
    while (x->left != NULL)
        x = x->left;
    return x->key;
}

int maxvalue(tree t)
{
    node x = t->root;
    while (x->right != NULL)
        x = x->right;
    return x->key;
}

node predecessor(tree t, int k)
{
    node x = search(t, k);
    if (x == NULL)
        return x;
    node p, y;
    if (x->left != NULL)
    {
        p = treemax(x->left);
        return p;
    }
    y = x->p;
    while (y != NULL && x == y->left)
    {
        x = y;
        y = y->p;
    }
    return y;
}

node successor(tree t, int k)
{
    node x = search(t, k);
    if (x == NULL)
        return x;
    node p, y;
    if (x->right != NULL)
    {
        p = treemin(x->right);
        return p;
    }
    y = x->p;
    while (y != NULL && x == y->right)
    {
        x = y;
        y = y->p;
    }
    return y;
}

int levels(node t, int k)
{
    if (t == NULL)
        return 0;
    if (t->key == k)
        return 1;
    if (k < t->key)
        return 1 + levels(t->left, k);
    else
        return 1 + levels(t->right, k);
}

int level(tree t, int k)
{
    node n = search(t, k);
    if (n == NULL)
        return -1;
    else
        return levels(t->root, k);
}

void inorders(node t)
{
    if (t != NULL)
    {
        inorders(t->left);
        printf("%d ", t->key);
        inorders(t->right);
    }
}

void preorders(node t)
{
    if (t != NULL)
    {
        printf("%d ", t->key);
        preorders(t->left);
        preorders(t->right);
    }
}

void postorders(node t)
{
    if (t != NULL)
    {
        postorders(t->left);
        postorders(t->right);
        printf("%d ", t->key);
    }
}

void inorder(tree t)
{
    inorders(t->root);
    printf("\n");
}

void preorder(tree t)
{
    preorders(t->root);
    printf("\n");
}

void postorder(tree t)
{
    postorders(t->root);
    printf("\n");
}
int main()
{
    char c;
    int k, x;
    node n;
    tree t = (tree)malloc(sizeof(struct tree));
    t->root = NULL;
    while (c != 'e')
    {
        c = getchar();
        switch (c)
        {
        case 'a':
            scanf("%d", &k);
            n = createnode(k);
            insert(t, n);
            break;
        case 'd':
            scanf("%d", &k);
            n = search(t, k);
            if (n == NULL)
                printf("%d\n", -1);
            else
            {
                delete (t, n);
            }
            break;
        case 's':
            scanf("%d", &k);
            n = search(t, k);
            if (n == NULL)
                printf("%d\n", -1);
            else
                printf("%d\n", 1);
            break;
        case 'l':
            scanf("%d", &k);
            x = level(t, k);
            printf("%d\n", x);
            break;
        case 'm':
            n = treemin(t->root);
            printf("%d\n", n->key);
            break;
        case 'x':
            n = treemax(t->root);
            printf("%d\n", n->key);
            break;
        case 'r':
            scanf("%d", &k);
            n = predecessor(t, k);
            if (n == NULL)
                printf("%d\n", -1);
            else
                printf("%d\n", n->key);
            break;
        case 'u':
            scanf("%d", &k);
            n = successor(t, k);
            if (n == NULL)
                printf("%d\n", -1);
            else
                printf("%d\n", n->key);
            break;
        case 'i':
            inorder(t);
            break;
        case 'p':
            preorder(t);
            break;
        case 't':
            postorder(t);
            break;
        }
    }
}