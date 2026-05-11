#include <stdio.h>
#include <math.h>

int is_prime(long long n)
{
    if (n <= 1)
        return 0;

    if (n == 2)
        return 1;

    if (n % 2 == 0)
        return 0;

    for (long long i = 3; i <= sqrt(n); i += 2)
    {
        if (n % i == 0)
            return 0;
    }

    return 1;
}

int main()
{
    long long test_num = 65537;

    if (is_prime(test_num))
        printf("%lld is PRIME\n", test_num);
    else
        printf("%lld is NOT PRIME\n", test_num);

    return 0;
} // gcc lab6_prime_check.c -o lab6_prime_check -lm
