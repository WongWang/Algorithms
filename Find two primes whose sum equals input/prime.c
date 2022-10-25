#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main(void)
{
    int n;
    scanf("%d", &n);
    int * prime = (int *) malloc(n * sizeof(int));

    int count = 0;
    for (int i = 2; i < n; ++i)
    {
        bool isprime = true;
        for (int j = 2; j < i; j++)
        {
            if (i % j == 0)
                isprime = false;
        }
        if (isprime)
        {
            prime[count] = i;
            count++;
        }
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = i; j < n; j++)
        {
            if (prime[i] + prime[j] == n)
                printf("%d=%d+%d\n", n, prime[i], prime[j]);
        }
    }

    return 0;
}
