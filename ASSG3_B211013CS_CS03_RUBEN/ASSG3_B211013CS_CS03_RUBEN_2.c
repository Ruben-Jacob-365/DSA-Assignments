#include <stdio.h>
#include <stdlib.h>

struct heap
{
    int arr[1000];
    int size;
};
typedef struct heap *heap;

void swap(int *x, int *y)
{
    int t = *x;
    *x = *y;
    *y = t;
}

int parent(int i)
{
    return ((i - 1) / 2);
}

void heapify(heap h, int i)
{
    int l = 2 * i + 1, r = 2 * i + 2;
    int min = i;
    if (l < h->size && h->arr[l] < h->arr[i])
        min = l;
    if (r < h->size && h->arr[r] < h->arr[min])
        min = r;
    if (min != i)
    {
        swap(&h->arr[i], &h->arr[min]);
        heapify(h, min);
    }
}

void build(heap h)
{
    for (int i = (h->size - 1) / 2; i >= 0; i--)
        heapify(h, i);
}

void insert(heap h, int x)
{
    h->size++;
    int i = h->size - 1;
    h->arr[i] = x;
    while (i != 0 && h->arr[parent(i)] > h->arr[i])
    {
        swap(&h->arr[parent(i)], &h->arr[i]);
        i = parent(i);
    }
}

void decreasekey(heap h, int x, int y)
{
    int i = 0;
    for (i = 0; i < h->size; i++)
    {
        if (h->arr[i] == x)
            break;
    }
    h->arr[i] = y;
    while (i != 0 && h->arr[parent(i)] > h->arr[i])
    {
        swap(&h->arr[i], &h->arr[parent(i)]);
        i = parent(i);
    }
}

int extractmin(heap h)
{
    int min = h->arr[0];
    h->arr[0] = h->arr[h->size - 1];
    h->size--;
    heapify(h, 0);
    return min;
}

void delete(heap h, int x)
{
    decreasekey(h, x, -1000001);
    extractmin(h);
}

int getmin(heap h)
{
    return h->arr[0];
}

int main()
{
    char c;
    int k, x;
    int n = 0;
    int i, j, f;
    heap h = (heap)malloc(sizeof(struct heap));
    h->size = 0;
    while (c != 'e')
    {
        c = getchar();
        switch (c)
        {
        case 'i':
            scanf("%d", &x);
            insert(h, x);
            break;
        case 'd':
            scanf("%d", &k);
            f = 0;
            for (j = 0; j < h->size; j++)
            {
                if (h->arr[j] == k)
                    f = 1;
            }
            if (!f)
            {
                printf("%d\n", -1);
                break;
            }
            delete (h, k);
            printf("%d\n", k);
            break;
        case 'p':
            for (i = 0; i < h->size; i++)
                printf("%d ", h->arr[i]);
            printf("\n");
            break;
        case 'x':
            extractmin(h);
            for (i = 0; i < h->size; i++)
                printf("%d ", h->arr[i]);
            printf("\n");
            break;
        case 'r':
            scanf("%d %d", &k, &x);
            if (x > k)
            {
                printf("%d\n", -1);
                break;
            }
            decreasekey(h, k, x);
            printf("%d\n", x);
            break;
        case 'g':
            printf("%d\n", getmin(h));
            break;
        }
    }
}
