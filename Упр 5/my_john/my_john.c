#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <crypt.h>

#define MAX_LINE 512

int dictionary_attack(const char *hash, const char *dict_file, char *found)
{
    FILE *file = fopen(dict_file, "r");
    if (!file)
        return 0;

    char word[256];

    while (fgets(word, sizeof(word), file))
    {
        word[strcspn(word, "\n")] = 0;

        char *computed = crypt(word, hash);

        if (strcmp(computed, hash) == 0)
        {
            strcpy(found, word);
            fclose(file);
            return 1;
        }
    }

    fclose(file);
    return 0;
}

int brute_force_pin(const char *hash, char *found)
{
    char guess[5];

    for (int i = 0; i <= 9999; i++)
    {
        sprintf(guess, "%04d", i);

        char *computed = crypt(guess, hash);

        if (strcmp(computed, hash) == 0)
        {
            strcpy(found, guess);
            return 1;
        }
    }

    return 0;
}

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("Usage: %s shadow.txt dictionary.txt\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (!file)
    {
        printf("Cannot open shadow file\n");
        return 1;
    }

    char line[MAX_LINE];

    printf("--- RESULTS ---\n");

    while (fgets(line, sizeof(line), file))
    {
        line[strcspn(line, "\n")] = 0;

        char *user = strtok(line, ":");
        char *hash = strtok(NULL, ":");

        if (!user || !hash)
            continue;

        char found[256] = "NOT CRACKED";

        if (dictionary_attack(hash, argv[2], found))
        {
            printf("%s : %s (dictionary)\n", user, found);
        }
        else if (brute_force_pin(hash, found))
        {
            printf("%s : %s (brute-force)\n", user, found);
        }
        else
        {
            printf("%s : [NOT CRACKED]\n", user);
        }
    }

    fclose(file);

    return EXIT_SUCCESS;
} // openssl passwd -6 -salt salt 7654
// gcc my_john.c -o my_john -lcrypt
// sed -i 's/\r$//' dictionary.txt
// ./my_john shadow.txt dictionary.txt
