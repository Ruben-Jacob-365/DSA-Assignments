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

int leaf(node t)
{
    if (t != NULL)
    {
        if (t->left == NULL && t->right == NULL)
            return 1;
        else
            return 0;
    }
}
int check(node t)
{
    if (t != NULL)
    {
        if (t->p != NULL && t->p->p != NULL)
        {
            if (leaf(t->p->p->left) || leaf(t->p->p->right))
                return 1 + check(t->left) + check(t->right);
        }
        return 0 + check(t->left) + check(t->right);
    }
    return 0;
}

void print(node t)
{
    if (t != NULL)
    {
        printf("%d ", t->key);
        print(t->left);
        print(t->right);
    }
}

int main()
{
    tree t = (tree)malloc(sizeof(struct tree));
    char *e = (char *)malloc(1000 * sizeof(char));
    scanf("%[^\n]%*c", e);
    t->root = build(e);
    int c = check(t->root);
    printf("%d ", c);
}