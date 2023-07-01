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

node create(int n)
{
    node new = (node)malloc(sizeof(struct node));
    new->key = n;
    new->left = NULL;
    new->right = NULL;
    new->p = NULL;
    return new;
}

node build(char *e)
{
    e += 2;
    if (*e == ')')
        return NULL;
    int num = 0;
    while (*e >= '0' && *e <= '9')
    {
        num = num * 10 + *e - '0';
        e++;
    }
    node n = create(num);
    e++;
    n->left = build(e);
    if (n->left != NULL)
        n->left->p = n;
    e++;
    int t = 1;
    while (t != 0)
    {
        if (*e == '(')
            t++;
        if (*e == ')')
            t--;
        e++;
    }
    e++;
    n->right = build(e);
    if (n->right != NULL)
        n->right->p = n;
    return n;
}

node search(node t, int k)
{
    if (t == NULL || t->key == k)
        return t;
    if (k < t->key)
        return search(t->left, k);
    else
        return search(t->right, k);
}

void ancestors(node t)
{
    while (t->p != NULL)
    {
        printf("%d ", t->p->key);
        t = t->p;
    }
}

void print(node t)
{
    if (t != NULL)
    {
        print(t->left);
        printf("%d ", t->key);
        print(t->right);
    }
}
int main()
{
    char *e = (char *)malloc(1000 * sizeof(char));
    scanf("%[^\n]%*c", e);
    tree t = (tree)malloc(sizeof(struct tree));
    t->root = build(e);
    int k;
    scanf("%d", &k);
    node n = search(t->root, k);
    if (n == NULL || n == t->root)
    {
        printf("%d", -1);
        return 0;
    }
    ancestors(n);
}