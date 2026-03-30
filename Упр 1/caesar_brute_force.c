#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define LETTERS 26

void caesar_decrypt(char *input, char *output, int key)
{
    int len = strlen(input);

    for (int i = 0; i < len; i++)
    {
        char c = input[i];

        if (isupper(c))
        {
            output[i] = ((c - 'A' - key + LETTERS) % LETTERS) + 'A';
        }
        else
        {
            output[i] = c;
        }
    }

    output[len] = '\0';
}

void bruteforce_attack(char *cipher)
{
    char buffer[256];

    printf("--- BRUTE FORCE REPORT ---\n");

    for (int k = 1; k < LETTERS; k++)
    {
        caesar_decrypt(cipher, buffer, k);
        printf("[Key %02d] -> %s\n", k, buffer);
    }
}

int main()
{
    char cipher[] = "GJMZH DKNPH DN NDHKGT YPHHT OZSO JA OCZ KMDIODIB VIY OTKZNZOODIB DIYPNOMT";

    bruteforce_attack(cipher);

    return 0;
}