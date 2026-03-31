#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void my_rc4(unsigned char *key, int key_len, unsigned char *input, int input_len, unsigned char *output)
{
    unsigned char state[256];
    unsigned char tmp;
    unsigned char i = 0, j = 0;

    for (int idx = 0; idx < 256; idx++)
        state[idx] = idx;

    for (int idx = 0; idx < 256; idx++)
    {
        j = (j + state[idx] + key[idx % key_len]) % 256;
        tmp = state[idx];
        state[idx] = state[j];
        state[j] = tmp;
    }

    i = 0;
    j = 0;
    for (int idx = 0; idx < input_len; idx++)
    {
        i = (i + 1) % 256;
        j = (j + state[i]) % 256;

        tmp = state[i];
        state[i] = state[j];
        state[j] = tmp;

        unsigned char keystream = state[(state[i] + state[j]) % 256];
        output[idx] = input[idx] ^ keystream;
    }
}

int main()
{
    unsigned char key[] = "MySecret";
    unsigned char message[] = "HelloRC4";
    int len = strlen((char *)message);
    unsigned char encrypted[256];
    unsigned char decrypted[256];

    my_rc4(key, strlen((char *)key), message, len, encrypted);

    printf("Encrypted (Hex): ");
    for (int k = 0; k < len; k++)
        printf("%02X ", encrypted[k]);
    printf("\n");

    my_rc4(key, strlen((char *)key), encrypted, len, decrypted);
    decrypted[len] = '\0';
    printf("Decrypted: %s\n", decrypted);

    return EXIT_SUCCESS;
}