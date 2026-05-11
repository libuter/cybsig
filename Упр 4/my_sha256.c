#include <stdio.h>
#include <string.h>
#include <openssl/evp.h>

#define BUFFER_SIZE 1024

int main(int argc, char *argv[])
{

    if (argc != 2)
    {
        printf("Usage: %s <file>\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "rb");

    if (file == NULL)
    {
        printf("Cannot open file\n");
        return 1;
    }

    EVP_MD_CTX *mdctx;

    unsigned char buffer[BUFFER_SIZE];
    unsigned char hash[EVP_MAX_MD_SIZE];

    unsigned int hash_len;

    size_t bytes_read;

    // 1. Създаване на контекст
    mdctx = EVP_MD_CTX_new();

    // 2. Инициализация SHA-256
    EVP_DigestInit_ex(mdctx, EVP_sha256(), NULL);

    // 3. Четене на файла на части
    while ((bytes_read = fread(buffer, 1, BUFFER_SIZE, file)) > 0)
    {

        EVP_DigestUpdate(mdctx, buffer, bytes_read);
    }

    // 4. Финализиране
    EVP_DigestFinal_ex(mdctx, hash, &hash_len);

    // 5. Почистване
    EVP_MD_CTX_free(mdctx);

    fclose(file);

    // PRINT HASH
    printf("SHA-256: ");

    for (int i = 0; i < hash_len; i++)
    {

        printf("%02x", hash[i]);
    }

    printf("\n");

    return 0;
} // gcc my_sha256.c -o my_sha256 -lssl -lcrypto
// ./my_sha256 movie.mp4