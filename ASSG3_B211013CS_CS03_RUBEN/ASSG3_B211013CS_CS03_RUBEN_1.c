#include <stdio.h>
#include <Stdlib.h>

typedef struct node
{
    int key;
    char colour;
    struct node *left;
    struct node *right;
} *node;

typedef struct tree
{
    node root;
} *tree;

node nilnode()
{
    node new = (node)malloc(sizeof(struct node));
    new->left = NULL;
    new->right = NULL;
    new->colour = 'B';
    return new;
}

node create(int key)
{
    node new = (node)malloc(sizeof(struct node));
    new->key = key;
    new->colour = 'R';
    new->left = nilnode();
    new->right = nilnode();
    return new;
}

node leftrotate(node t)
{
    node a = t->right;
    node b = a->left;
    t->right = b;
    a->left = t;
    return a;
}

node rightrotate(node t)
{
    node a = t->left;
    node b = a->right;
    t->left = b;
    a->right = t;
    return a;
}

void print(node t)
{
    if (t->left != NULL)
    {
        printf("%d %c ", t->key, t->colour);
        printf("( ");
        print(t->left);
        printf(") ( ");
        print(t->right);
        printf(") ");
    }
}

node insert(node t, node n)
{
    if (t->left == NULL)
        return n;
    else if (n->key < t->key)
    {
        t->left = insert(t->left, n);
        if (t->left->colour == 'R')
        {
            if (t->left->left->colour == 'R' || t->left->right->colour == 'R')
            {
                if (t->right->colour == 'R')
                {
                    t->colour = 'R';
                    t->left->colour = 'B';
                    t->right->colour = 'B';
                    return t;
                }
                else
                {
                    if (t->left->right->colour == 'R')
                        t->left = leftrotate(t->left);
                    t = rightrotate(t);
                    t->colour = 'B';
                    t->right->colour = 'R';
                    return t;
                }
            }
            return t;
        }
        else
            return t;
    }
    else
    {
        t->right = insert(t->right, n);
        if (t->right->colour == 'R')
        {
            if (t->right->left->colour == 'R' || t->right->right->colour == 'R')
            {
                if (t->left->colour == 'R')
                {
                    t->colour = 'R';
                    t->right->colour = 'B';
                    t->left->colour = 'B';
                    return t;
                }
                else
                {
                    if (t->right->left->colour == 'R')
                        t->right = rightrotate(t->right);
                    t = leftrotate(t);
                    t->colour = 'B';
                    t->left->colour = 'R';
                    return t;
                }
            }
            return t;
        }
        else
            return t;
    }
}

void insertredblack(tree t, int key)
{
    node n = create(key);
    t->root = insert(t->root, n);
    t->root->colour = 'B';
    printf("( ");
    print(t->root);
    printf(")\n");
}

int main()
{
    tree t = (tree)malloc(sizeof(struct tree));
    t->root = nilnode();
    char *e = (char *)malloc(1000 * sizeof(char));
    while (1)
    {
        scanf("%[^\n]%*c", e);
        if (e[0] == 't')
            break;
        int num = 0, i = 0;
        while (e[i] >= '0' && e[i] <= '9')
        {
            num = num * 10 + e[i] - '0';
            i++;
        }
        insertredblack(t, num);
    }
}
