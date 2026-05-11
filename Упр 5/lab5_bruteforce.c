#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <crypt.h>

void crack_pin(const char *target_hash)
{

    char guess[5];

    printf("--- Start PIN Brute-Force ---\n");

    for (int i = 0; i <= 9999; i++)
    {

        sprintf(guess, "%04d", i);

        char *computed_hash = crypt(guess, target_hash); // crypt(password, salt/hash)

        if (strcmp(computed_hash, target_hash) == 0)
        {
            printf("[SUCCESS] PIN: %s\n", guess);
            return;
        }
    }

    printf("[FAIL] Not found\n");
}

int main()
{

    // ВАЖНО: используем хеш из задания (alice)
    char hash[] =
        "$6$xq7%3$03TJMkvoZmSoSVmWpDUuBvXNInUeIT3fLj6EvodCh1qFYjK9azoiyfxT4/gomNcpX.5Xfg08ZPU6U.xIHu8Pn.";

    crack_pin(hash);

    return EXIT_SUCCESS;
} // gcc lab5_bruteforce.c -o lab5_bruteforce -lcrypt