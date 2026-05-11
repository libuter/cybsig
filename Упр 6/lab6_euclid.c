#include <stdio.h>

long long gcd(long long a, long long b)
{
    while (b != 0)
    {
        long long temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int main()
{
    printf("GCD of 48 and 18 is: %lld\n", gcd(48, 18));
    printf("GCD of 65537 and 3120 is: %lld\n", gcd(65537, 3120));

    return 0;
}// gcc lab6_euclid.c -o lab6_euclid