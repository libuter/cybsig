#include <stdio.h>
#include <string.h>
#include <openssl/evp.h>

void calculate_sha256(const char *message, unsigned char *digest, unsigned int *digest_len)
{
    EVP_MD_CTX *mdctx;

    // 1. Създаване на контекст
    if ((mdctx = EVP_MD_CTX_new()) == NULL)
    {
        printf("Error creating context\n");
        return;
    }

    // 2. Инициализация (Избираме SHA-256)
    EVP_DigestInit_ex(mdctx, EVP_sha256(), NULL);

    // 3. Добавяне на данните (Update)
    EVP_DigestUpdate(mdctx, message, strlen(message));

    // 4. Финализиране (Final)
    EVP_DigestFinal_ex(mdctx, digest, digest_len);

    // 5. Почистване
    EVP_MD_CTX_free(mdctx);
}

int main()
{

    char message1[] = "Trust";
    char message2[] = "Rust";

    unsigned char hash1[EVP_MAX_MD_SIZE];
    unsigned char hash2[EVP_MAX_MD_SIZE];

    unsigned int hash1_len;
    unsigned int hash2_len;

    printf("Message 1: %s\n", message1);
    printf("Message 2: %s\n\n", message2);

    // HASH 1
    calculate_sha256(message1, hash1, &hash1_len);

    // HASH 2
    calculate_sha256(message2, hash2, &hash2_len);

    // PRINT HASH 1
    printf("SHA-256 Hash 1:\n");
    for (int i = 0; i < hash1_len; i++)
    {
        printf("%02x", hash1[i]);
    }

    printf("\n\n");

    // PRINT HASH 2
    printf("SHA-256 Hash 2:\n");
    for (int i = 0; i < hash2_len; i++)
    {
        printf("%02x", hash2[i]);
    }

    printf("\n");

    return 0;
}// gcc sha256.c -o sha256 -lssl -lcrypto
/* openssl sha256 msg1.txt
SHA2-256(msg1.txt)= ade9248e0132b4112c81e94cce392e1068029bac214f23c79d10693e781a16f1
lisa@Lisa-pc:/mnt/c/AAAAA/ProgrVS$ openssl sha256 msg2.txt
SHA2-256(msg2.txt)= d9aa89fdd15ad5c41d9c128feffe9e07dc828b83f85296f7f42bda506821300e */