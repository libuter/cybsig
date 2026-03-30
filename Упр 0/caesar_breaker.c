#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#define LETTERS 26

char decrypt_char(char c, int key)
{
    if (isupper(c))
        return ((c - 'A' - key + LETTERS) % LETTERS) + 'A';
    return c; 
}

void decrypt_with_key(char *cipher, int key)
{
    int len = strlen(cipher);

    for (int i = 0; i < len; i++)
    {
        printf("%c", decrypt_char(cipher[i], key));
    }
}

int main()
{
    char cipher[] = "WKLV LV D VHFUHW PHVVDJH";

    printf("Cipher text: %s\n\n", cipher);
    printf("---- Brute Force Results ----\n");

    for (int key = 1; key < LETTERS; key++)
    {
        printf("Key %d: ", key);
        decrypt_with_key(cipher, key);
        printf("\n");
    }
    return EXIT_SUCCESS;
}
