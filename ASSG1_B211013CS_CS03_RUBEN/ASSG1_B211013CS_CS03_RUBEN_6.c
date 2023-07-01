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

node create(int k)
{
    node new = (node)malloc(sizeof(struct node));
    new->key = k;
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
    return n;
}

void find(node t, int x, int y)
{
    if (t != NULL)
    {
        find(t->left, x, y);
        if (t->key >= x && t->key <= y)
            printf("%d ", t->key);
        find(t->right, x, y);
    }
}

int main()
{
    char *e = (char *)malloc(1000 * sizeof(char));
    scanf("%[^\n]%*c", e);
    tree t = (tree)malloc(sizeof(struct tree));
    t->root = build(e);
    int x, y;
    scanf("%d %d", &x, &y);
    find(t->root, x, y);
}