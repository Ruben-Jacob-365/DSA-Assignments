#include <stdio.h>
#include <stdlib.h>

typedef struct hashtable
{
    int size;
    int *index;
} *hashtable;

int prime(int n)
{
    if (n == 2)
        return 1;
    for (int i = 2; i < n; i++)
    {
        if (n % i == 0)
            return 0;
    }
    return 1;
}

int nearestprime(int n)
{
    for (int i = n - 1; i >= 2; i--)
    {
        if (prime(i))
            return i;
    }
    return -1;
}

int hash(int key, int n)
{
    return key % n;
}

int linearhash(int key, int n, int i)
{
    return (hash(key, n) + i) % n;
}
int quadhash(int key, int n, int i)
{
    return (hash(key, n) + i * i) % n;
}

int doublehash(int key, int n, int i)
{
    int h1 = hash(key, n);
    int r = nearestprime(n);
    int h2 = r - (key % r);
    return (h1 + i * h2) % n;
}

int linearprobing(hashtable table, int a[], int n)
{
    int hf, j = 0, lp = 0;
    for (int i = 0; i < n; i++)
    {
        j = 0;
        hf = linearhash(a[i], table->size, j);
        while (table->index[hf] != -1)
        {
            lp++;
            j++;
            hf = linearhash(a[i], table->size, j);
        }
        table->index[hf] = a[i];
        printf("%d ", hf);
    }
    return lp;
}

int quadprobing(hashtable table, int a[], int n)
{
    int hf, j = 0, qp = 0, c = 0, e = 0;
    for (int i = 0; i < n; i++)
    {
        j = 0;
        hf = quadhash(a[i], table->size, j);
        c = 0;
        while (table->index[hf] != -1)
        {
            c++;
            if (c >= table->size)
            {
                e = 1;
                break;
            }
            j++;
            hf = quadhash(a[i], table->size, j);
        }
        qp += c;
        if (!e)
        {
            table->index[hf] = a[i];
            printf("%d ", hf);
        }
        else
        {
            printf("E ");
            e = 0;
        }
    }
    return qp;
}

int doublehashing(hashtable table, int a[], int n)
{
    int hf, j = 0, dh = 0, c = 0, e = 0;
    for (int i = 0; i < n; i++)
    {
        j = 0;
        hf = doublehash(a[i], table->size, j);
        c = 0;
        while (table->index[hf] != -1)
        {
            c++;
            if (c >= table->size)
            {
                e = 1;
                break;
            }
            j++;
            hf = doublehash(a[i], table->size, j);
        }
        dh += c;
        if (!e)
        {
            table->index[hf] = a[i];
            printf("%d ", hf);
        }
        else
        {
            printf("E ");
            e = 0;
        }
    }
    return dh;
}

int main()
{
    int n;
    scanf("%d", &n);
    hashtable table = (hashtable)malloc(sizeof(struct hashtable));
    table->size = n;
    table->index = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < table->size; i++)
        table->index[i] = -1;
    char *c = (char *)malloc(10000 * sizeof(char));
    scanf(" %[^\n]%*c", c);
    int i = 0, j = 0;
    int a[10000];
    while (c[i] != '\0')
    {
        int num = 0;
        if (c[i] >= '0' && c[i] <= '9')
        {
            while (c[i] >= '0' && c[i] <= '9')
            {
                num = num * 10 + c[i] - '0';
                i++;
            }
            a[j] = num;
            j++;
            continue;
        }
        i++;
    }
    int lp = 0, qp = 0, dh = 0;
    lp = linearprobing(table, a, j);
    printf("\n%d\n", lp);
    for (int i = 0; i < table->size; i++)
        table->index[i] = -1;
    qp = quadprobing(table, a, j);
    printf("\n%d\n", qp);
    for (int i = 0; i < table->size; i++)
        table->index[i] = -1;
    dh = doublehashing(table, a, j);
    printf("\n%d", dh);
}