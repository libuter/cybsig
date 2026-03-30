#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void xor_cipher(char *text, char key)
{
    int len = strlen(text);
    for (int i = 0; i < len; i++)
    {
        text[i] ^= key;
    }
}

int main()
{
    char data[] = "Secret";
    char key = 'K';

    xor_cipher(data, key);
    printf("Encrypted: ");
    for (int i = 0; i < strlen(data); i++)
    {
        printf("%02X ", (unsigned char)data[i]);
    }
    printf("\n");

    xor_cipher(data, key);
    printf("Decrypted: %s\n", data);

    return EXIT_SUCCESS;
}
