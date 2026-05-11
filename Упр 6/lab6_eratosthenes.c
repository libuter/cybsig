#include <stdio.h>
#include <stdlib.h>

void sieve_of_eratosthenes(int max)
{
    int *primes = malloc((max + 1) * sizeof(int));

    for (int i = 0; i <= max; i++)
        primes[i] = 1;

    primes[0] = 0;
    primes[1] = 0;

    for (int p = 2; p * p <= max; p++)
    {
        if (primes[p] == 1)
        {
            for (int i = p * p; i <= max; i += p)
            {
                primes[i] = 0;
            }
        }
    }

    printf("Prime numbers up to %d: ", max);

    for (int p = 2; p <= max; p++)
    {
        if (primes[p])
            printf("%d ", p);
    }

    printf("\n");

    free(primes);
}

int main()
{
    int max = 1000;

    sieve_of_eratosthenes(max);

    return EXIT_SUCCESS;
} // gcc lab6_eratosthenes.c -o lab6_eratosthenes
// ./lab6_eratosthenes