#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{

    // АЛИСА
    time_t seed_alice = time(NULL);
    srand(seed_alice);

    int token = rand();

    printf("Alice token: %d\n", token);
    printf("Generated at: %ld\n", seed_alice);

    // ЕВА
    printf("\n--- Eve attack ---\n");

    time_t current_time = time(NULL);
    int cracked = 0;

    for (time_t guess_seed = current_time - 600; guess_seed <= current_time; guess_seed++)
    {

        srand(guess_seed);
        int guess = rand();

        if (guess == token)
        {
            printf("[FOUND] Seed = %ld\n", guess_seed);

            printf("Next numbers: %d %d %d\n", rand(), rand(), rand());

            cracked = 1;
            break;
        }
    }

    if (!cracked)
    {
        printf("Failed to find seed\n");
    }

    return EXIT_SUCCESS;
}