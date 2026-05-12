#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <openssl/evp.h>

void calculate_md5(const char *message, unsigned char *digest, unsigned int *digest_len)
{
    EVP_MD_CTX *mdctx;

    if ((mdctx = EVP_MD_CTX_new()) == NULL)
    {
        printf("Error creating context\n");
        return;
    }

    EVP_DigestInit_ex(mdctx, EVP_md5(), NULL);
    EVP_DigestUpdate(mdctx, message, strlen(message));
    EVP_DigestFinal_ex(mdctx, digest, digest_len);

    EVP_MD_CTX_free(mdctx);
}

void to_hex(unsigned char *hash, unsigned int len, char *output)
{
    for (unsigned int i = 0; i < len; i++)
    {
        sprintf(output + (i * 2), "%02x", hash[i]);
    }
    output[len * 2] = '\0';
}

int main()
{
    const char target_hash[] = "9daae68368ac7be2d9902bb79b556c04";

    char guess[5];
    char message[32];
    unsigned char hash[EVP_MAX_MD_SIZE];
    unsigned int hash_len;
    char hash_hex[65];

    printf("--- Start MD5 Brute Force ---\n");

    for (int i = 0; i <= 9999; i++)
    {
        sprintf(guess, "%04d", i);

        sprintf(message, "LAB_%s", guess);

        calculate_md5(message, hash, &hash_len);
        to_hex(hash, hash_len, hash_hex);

        if (strcmp(hash_hex, target_hash) == 0)
        {
            printf("[SUCCESS] PIN found: %s\n", guess);
            printf("Full string: %s\n", message);
            return 0;
        }
    }

    printf("[FAIL] PIN not found\n");
    return EXIT_SUCCESS;
}