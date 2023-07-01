#include <stdio.h>
#include <stdlib.h>
typedef struct node
{
    char name[1000];
    char branch[1000];
    struct node *next;
} *node;

typedef struct list
{
    node head;
} *list;

typedef struct hashtable
{
    list *hashlist;
    int size;
} *hashtable;

int hash(char name[], int age)
{
    int i = 0, hf = 0;
    while (name[i] != '\0')
    {
        hf += name[i];
        i++;
    }
    hf += age;
    return hf % 4;
}

void copy(char a[], char b[])
{
    int i = 0;
    while (b[i] != '\0')
    {
        a[i] = b[i];
        i++;
    }
    a[i] = '\0';
}

node createnode(char name[], char branch[])
{
    node new = (node)malloc(sizeof(struct node));
    copy(new->name, name);
    copy(new->branch, branch);
    new->next = NULL;
    return new;
}

void listinsert(list l, node n)
{
    if (l->head == NULL)
    {
        l->head = n;
        return;
    }
    node t = l->head;
    while (t->next != NULL)
        t = t->next;
    t->next = n;
}

void printlist(list l)
{
    node t = l->head;
    while (t != NULL)
    {
        printf("%s ", t->name);
        t = t->next;
    }
}

int noitems(list l)
{
    if (l->head == NULL)
        return 0;
    node t = l->head;
    int c = 0;
    while (t != NULL)
    {
        c++;
        t = t->next;
    }
    return c;
}

int compare(char a[], char b[])
{
    int i = 0;
    while (a[i] != '\0')
    {
        if (a[i] - b[i] != 0)
            return a[i] - b[i];
        i++;
    }
    return 0;
}

void listsearch(list l, char branch[])
{
    node t = l->head;
    if (t == NULL)
    {
        printf("%d\n", -1);
        return;
    }
    int c = 0;
    while (t != NULL)
    {
        if (compare(t->branch, branch) == 0)
        {
            printf("%s ", t->name);
            c++;
        }
        t = t->next;
    }
    if (c == 0)
    {
        printf("%d\n", -1);
        return;
    }
    printf("\n");
}

int main()
{
    hashtable table = (hashtable)malloc(sizeof(hashtable));
    int n;
    scanf("%d", &n);
    table->size = 4;
    table->hashlist = (list *)malloc(4 * sizeof(struct list));
    for (int i = 0; i < 4; i++)
    {
        table->hashlist[i] = (list)malloc(sizeof(struct list));
        table->hashlist[i]->head = NULL;
    }
    char name[1000], rollno[1000], branch[2];
    int age, hv;
    while (n--)
    {
        scanf("%s", name);
        scanf("%s", rollno);
        scanf("%d", &age);
        hv = hash(name, age);
        if (rollno[7] >= 'a' && rollno[7] <= 'z')
            rollno[7] = rollno[7] - 32;
        if (rollno[8] >= 'a' && rollno[8] <= 'z')
            rollno[8] = rollno[8] - 32;
        branch[0] = rollno[7];
        branch[1] = rollno[8];
        branch[2] = '\0';
        node new = createnode(name, branch);
        listinsert(table->hashlist[hv], new);
    }
    char ch;
    int k, x;
    while (ch != 'e')
    {
        ch = getchar();
        switch (ch)
        {
        case 'c':
            scanf("%d", &k);
            x = noitems(table->hashlist[k]);
            printf("%d ", x);
            if (x)
                printlist(table->hashlist[k]);
            printf("\n");
            break;
        case '0':
            scanf(" %[^\n]%*c", branch);
            if (branch[0] >= 'a' && branch[0] <= 'z')
                branch[0] = branch[0] - 32;
            if (branch[1] >= 'a' && branch[1] <= 'z')
                branch[1] = branch[1] - 32;
            listsearch(table->hashlist[0], branch);
            break;
        case '1':
            scanf(" %[^\n]%*c", branch);
            if (branch[0] >= 'a' && branch[0] <= 'z')
                branch[0] = branch[0] - 32;
            if (branch[1] >= 'a' && branch[1] <= 'z')
                branch[1] = branch[1] - 32;
            listsearch(table->hashlist[1], branch);
            break;
        case '2':
            scanf(" %[^\n]%*c", branch);
            if (branch[0] >= 'a' && branch[0] <= 'z')
                branch[0] = branch[0] - 32;
            if (branch[1] >= 'a' && branch[1] <= 'z')
                branch[1] = branch[1] - 32;
            listsearch(table->hashlist[2], branch);
            break;
        case '3':
            scanf(" %[^\n]%*c", branch);
            if (branch[0] >= 'a' && branch[0] <= 'z')
                branch[0] = branch[0] - 32;
            if (branch[1] >= 'a' && branch[1] <= 'z')
                branch[1] = branch[1] - 32;
            listsearch(table->hashlist[3], branch);
            break;
        }
    }
}
