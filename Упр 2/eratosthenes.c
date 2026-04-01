#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()
{
    int N;
    scanf("%d", &N);

    if (N < 2 || N > 1000000)
    {
        printf("Invalid input\n");
        return 1;
    }

    char *is_prime = malloc((N + 1) * sizeof(char));
    if (!is_prime)
    {
        printf("Memory error\n");
        return 1;
    }

    for (int i = 0; i <= N; i++)
        is_prime[i] = 1;

    is_prime[0] = 0;
    is_prime[1] = 0;

    for (int i = 2; i * i <= N; i++)
    {
        if (is_prime[i])
        {
            for (int j = i * i; j <= N; j += i)
            {
                is_prime[j] = 0;
            }
        }
    }

    int count = 0;
    int max_prime = 2;

    for (int i = 2; i <= N; i++)
    {
        if (is_prime[i])
        {
            printf("%d ", i); // ← вывод всех простых
            count++;
            max_prime = i;
        }
    }
    printf("\n");

    printf("Count: %d\n", count);
    printf("Max prime: %d\n", max_prime);

    free(is_prime);
    return 0;
}
