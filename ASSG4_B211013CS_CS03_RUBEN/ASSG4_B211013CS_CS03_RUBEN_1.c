#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n;
    scanf("%d", &n);
    int adj[n][n];
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            scanf("%d", &adj[i][j]);
    }
    for (int i = 0; i < n; i++)
    {
        printf("%d ", i);
        for (int j = 0; j < n; j++)
        {
            if (adj[i][j] == 1)
                printf("%d ", j);
        }
        printf("\n");
    }
}