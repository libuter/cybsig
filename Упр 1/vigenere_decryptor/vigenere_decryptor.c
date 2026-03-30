#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAXN 1000

char *vigenere_encrypt(const char *plaintext, const char *key)
{
    int plaintext_len = strlen(plaintext);
    int key_len = strlen(key);
    int key_index = 0;
    char *output = malloc(sizeof(char) * (plaintext_len + 1));
    for (int i = 0; i < plaintext_len; i++)
    {

        char symbol = plaintext[i];
        if (isalpha(symbol))
        {

            char key_symbol = toupper(key[key_index % key_len]);
            int shift = key_symbol - 'A';

            if (isupper(symbol))
            {

                output[i] = ((symbol - 'A' + shift) % 26) + 'A';
            }
            else if (islower(symbol))
            {
                output[i] = ((symbol - 'a' + shift) % 26) + 'a';
            }

            key_index++;
        }
        else
        {
            output[i] = plaintext[i];
        }
    }

    output[plaintext_len] = '\0';
    return output;
}

char *vigenere_decrypt(const char *cipher, const char *key)
{
    int cipher_len = strlen(cipher);
    int key_len = strlen(key);
    int key_index = 0;
    char *output = malloc(sizeof(char) * (cipher_len + 1));
    for (int i = 0; i < cipher_len; i++)
    {

        char symbol = cipher[i];
        if (isalpha(symbol))
        {

            char key_symbol = toupper(key[key_index % key_len]);
            int shift = key_symbol - 'A';

            if (isupper(symbol))
            {

                output[i] = ((symbol - 'A' - shift + 26) % 26) + 'A';
            }
            else if (islower(symbol))
            {
                output[i] = ((symbol - 'a' - shift + 26) % 26) + 'a';
            }

            key_index++;
        }
        else
        {
            output[i] = cipher[i];
        }
    }

    output[cipher_len] = '\0';
    return output;
}

int main()
{
    FILE *fin = fopen("vigenere_encrypted.txt", "r");
    FILE *fkey = fopen("vigenere_key.txt", "r");
    FILE *fout = fopen("vigenere_decrypted.txt", "w");

    if (!fin || !fkey || !fout)
    {
        perror("File error");
        return EXIT_FAILURE;
    }

    char text[MAXN];
    char key[MAXN];

    fgets(text, MAXN, fin);
    fscanf(fkey, "%s", key);

    fclose(fin);
    fclose(fkey);

    char *result = vigenere_decrypt(text, key);

    fprintf(fout, "%s", result);

    fclose(fout);
    free(result);

    printf("Decryption completed!\n");

    return EXIT_SUCCESS;
}