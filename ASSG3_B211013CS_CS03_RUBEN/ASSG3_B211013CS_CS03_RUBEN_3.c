#include <stdio.h>
#include <stdlib.h>

struct heap
{
    int arr[1000];
    int size;
};
typedef struct heap *heap;

int swap(int *x, int *y)
{
    int t = *x;
    *x = *y;
    *y = t;
}

void heapify(heap h, int i)
{
    int l = 2 * i + 1, r = 2 * i + 2, max = i;
    if (l < h->size && h->arr[l] > h->arr[i])
        max = l;
    if (r < h->size && h->arr[r] > h->arr[max])
        max = r;
    if (max != i)
    {
        swap(&h->arr[i], &h->arr[max]);
        heapify(h, max);
    }
}

void build(heap h)
{
    for (int i = (h->size - 1) / 2; i >= 0; i--)
    {
        heapify(h, i);
    }
}

int extractmax(heap h)
{
    int max = h->arr[0];
    h->arr[0] = h->arr[h->size - 1];
    h->size--;
    heapify(h, 0);
    return max;
}

int main()
{
    int t;
    scanf("%d", &t);
    while (t--)
    {
        int n;
        heap h = (heap)malloc(sizeof(struct heap));
        scanf("%d", &n);
        h->size = n;
        int i, k;
        for (i = 0; i < n; i++)
            scanf("%d", &h->arr[i]);
        build(h);
        scanf("%d", &k);
        while (k--)
        {
            printf("%d ", extractmax(h));
        }
        printf("\n");
    }
}
