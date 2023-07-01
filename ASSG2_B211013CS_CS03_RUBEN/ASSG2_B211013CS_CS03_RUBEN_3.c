#include <stdio.h>
#include <stdlib.h>

typedef struct hashtable
{
    int index[10000];
} *hashtable;

int main()
{
    int n;
    hashtable tablea = (hashtable)malloc(sizeof(struct hashtable));
    hashtable tableb = (hashtable)malloc(sizeof(struct hashtable));
    scanf("%d", &n);
    for (int i = 0; i < 10000; i++)
    {
        tablea->index[i] = 0;
        tableb->index[i] = 0;
    }
    int a[n], b[n];
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &a[i]);
        tablea->index[a[i]]++;
    }
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &b[i]);
        tableb->index[b[i]]++;
    }
    for (int i = 0; i < 10000; i++)
    {
        if (tablea->index[i] != tableb->index[i])
        {
            printf("%d", 0);
            return 0;
        }
    }
    printf("%d", 1);
    return 0;
}