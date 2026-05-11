#include <stdio.h>
#include <math.h>

void factorize_rsa(long long n)
{
    printf("--- Start factorization of N = %lld ---\n", n);

    long long limit = (long long)sqrt(n);

    // проверяем 2 отдельно (если вдруг чётное)
    if (n % 2 == 0)
    {
        long long p = 2;
        long long q = n / 2;

        printf("[SUCCESS]\n");
        printf("p = %lld\n", p);
        printf("q = %lld\n", q);

        long long phi = (p - 1) * (q - 1);
        printf("Phi(n) = %lld\n", phi);

        return;
    }

    for (long long i = 3; i <= limit; i += 2)
    {
        if (n % i == 0)
        {
            long long p = i;
            long long q = n / i;

            printf("[SUCCESS] Found factors!\n");
            printf("p = %lld\n", p);
            printf("q = %lld\n", q);

            long long phi = (p - 1) * (q - 1);
            printf("Phi(n) = %lld\n", phi);

            return;
        }
    }

    printf("No factors found. Number might be prime.\n");
}

int main()
{
    long long public_n = 3233; // test RSA modulus

    factorize_rsa(public_n);

    return 0;
}// gcc lab6_rsa.c -o lab6_rsa -lm
// ./lab6_rsa