#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void rc4(unsigned char *key, int key_len,
         unsigned char *data, int data_len)
{
    unsigned char S[256];
    unsigned char temp;
    int i, j;

    for (i = 0; i < 256; i++)
        S[i] = i;

    j = 0;
    for (i = 0; i < 256; i++)
    {
        j = (j + S[i] + key[i % key_len]) % 256;

        temp = S[i];
        S[i] = S[j];
        S[j] = temp;
    }

    i = 0;
    j = 0;

    for (int k = 0; k < data_len; k++)
    {
        i = (i + 1) % 256;
        j = (j + S[i]) % 256;

        temp = S[i];
        S[i] = S[j];
        S[j] = temp;

        unsigned char keystream = S[(S[i] + S[j]) % 256];

        data[k] ^= keystream; // XOR прямо в буфере
    }
}

int main(int argc, char *argv[])
{
    if (argc != 4)
    {
        printf("Usage: %s input_file output_file password\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *input_name = argv[1];
    char *output_name = argv[2];
    char *password = argv[3];

    FILE *fin = fopen(input_name, "rb");
    FILE *fout = fopen(output_name, "wb");

    if (!fin || !fout)
    {
        perror("File error");
        return EXIT_FAILURE;
    }

    fseek(fin, 0, SEEK_END);
    long size = ftell(fin);
    rewind(fin);

    unsigned char *buffer = malloc(size);

    if (!buffer)
    {
        printf("Memory error\n");
        return EXIT_FAILURE;
    }

    fread(buffer, 1, size, fin);

    fclose(fin);

    rc4((unsigned char *)password, strlen(password), buffer, size);

    fwrite(buffer, 1, size, fout);

    fclose(fout);
    free(buffer);

    printf("Done!\n");

    return EXIT_SUCCESS;
}