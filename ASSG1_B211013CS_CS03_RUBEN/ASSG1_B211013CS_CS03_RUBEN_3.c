#include <stdio.h>
#include <stdlib.h>
struct node
{
    int key;
    struct node *left;
    struct node *right;
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

void print(node t)
{
    if (t != NULL)
    {
        print(t->left);
        printf("%d ", t->key);
        print(t->right);
    }
}

int sum(node t)
{
    if (t != NULL)
    {
        return t->key + sum(t->left) + sum(t->right);
    }
    return 0;
}
int find(node t, int x)
{
    if (t != NULL)
    {
        if (sum(t) == x)
            return (1 + find(t->left, x) + find(t->right, x));
        else
            return find(t->left, x) + find(t->right, x);
    }
    return 0;
}
int main()
{
    char *e = (char *)malloc(1000 * sizeof(char));
    scanf("%[^\n]%*c", e);
    tree t = (tree)malloc(sizeof(struct tree));
    t->root = build(e);
    int x;
    scanf("%d", &x);
    printf("%d", find(t->root, x));
}