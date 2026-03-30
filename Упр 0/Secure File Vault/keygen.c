#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        printf("Usage: %s <key_size>\n", argv[0]);
        return EXIT_FAILURE;
    }

    int size = atoi(argv[1]);

    FILE *key = fopen("otp.key", "wb");
    if (!key)
    {
        perror("Cannot create key file");
        return EXIT_FAILURE;
    }

    srand(time(NULL));

    for (int i = 0; i < size; i++)
    {
        unsigned char byte = rand() % 256;
        fwrite(&byte, 1, 1, key);
    }

    fclose(key);

    printf("Key generated: otp.key (%d bytes)\n", size);
    return EXIT_SUCCESS;
}