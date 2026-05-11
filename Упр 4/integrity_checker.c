#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <openssl/evp.h>

void calculate_sha256(const char *message,
                      unsigned char *digest,
                      unsigned int *digest_len)
{

    EVP_MD_CTX *mdctx;

    // 1. Създаване на контекст
    if ((mdctx = EVP_MD_CTX_new()) == NULL)
    {
        printf("Error creating context\n");
        return;
    }

    // 2. Инициализация
    EVP_DigestInit_ex(mdctx, EVP_sha256(), NULL);

    // 3. Добавяне на данните
    EVP_DigestUpdate(mdctx, message, strlen(message));

    // 4. Финализиране
    EVP_DigestFinal_ex(mdctx, digest, digest_len);

    // 5. Почистване
    EVP_MD_CTX_free(mdctx);
}

int main()
{

    char password[100];

    // SHA-256("admin")
    char stored_hash[] =
        "8c6976e5b5410415bde908bd4dee15dfb167a9c873fc4bb8a81f6f2ab448a918";

    unsigned char hash[EVP_MAX_MD_SIZE];
    unsigned int hash_len;

    char computed_hash_string[65]; // HEX: 2 символа на байт

    printf("Enter password: ");
    scanf("%99s", password);

    // HASH PASSWORD
    calculate_sha256(password, hash, &hash_len);

    // BIN -> HEX
    for (int i = 0; i < hash_len; i++)
    {
        sprintf(computed_hash_string + (i * 2), "%02x", hash[i]);
    }

    computed_hash_string[64] = '\0';

    printf("Computed Hash:\n%s\n", computed_hash_string);

    // COMPARE
    if (strcmp(computed_hash_string, stored_hash) == 0)
    {
        printf("ACCESS GRANTED!\n");
    }
    else
    {
        printf("ACCESS DENIED!\n");
    }

    return EXIT_SUCCESS;
} // gcc integrity_checker.c -o integrity_checker -lssl -lcrypto
/* ./integrity_checker
Enter password: admin
Computed Hash:
8c6976e5b5410415bde908bd4dee15dfb167a9c873fc4bb8a81f6f2ab448a918
ACCESS GRANTED! */