#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <openssl/evp.h>

void handleErrors()
{
    printf("OpenSSL error\n");
    exit(1);
}

// ENCRYPT
int encrypt(unsigned char *in, int inlen,
            unsigned char *key,
            unsigned char *out)
{

    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    int len, outlen;

    EVP_EncryptInit_ex(ctx, EVP_aes_128_ecb(), NULL, key, NULL);

    EVP_EncryptUpdate(ctx, out, &len, in, inlen);
    outlen = len;

    EVP_EncryptFinal_ex(ctx, out + len, &len);
    outlen += len;

    EVP_CIPHER_CTX_free(ctx);

    return outlen;
}

// DECRYPT
int decrypt(unsigned char *in, int inlen,
            unsigned char *key,
            unsigned char *out)
{

    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    int len, outlen;

    EVP_DecryptInit_ex(ctx, EVP_aes_128_ecb(), NULL, key, NULL);

    EVP_DecryptUpdate(ctx, out, &len, in, inlen);
    outlen = len;

    EVP_DecryptFinal_ex(ctx, out + len, &len);
    outlen += len;

    EVP_CIPHER_CTX_free(ctx);

    return outlen;
}

// HEX encode
void to_hex(unsigned char *in, int len, char *out)
{
    for (int i = 0; i < len; i++)
        sprintf(out + i * 2, "%02X", in[i]);
    out[len * 2] = '\0';
}

// HEX decode
int from_hex(char *in, unsigned char *out)
{
    int len = strlen(in);
    int real_len = len / 2;

    for (int i = 0; i < real_len; i++)
    {
        sscanf(in + 2 * i, "%2hhX", &out[i]);
    }

    return real_len;
}

int main()
{

    unsigned char key[16] = "0123456789012345";

    unsigned char plaintext[256];
    unsigned char ciphertext[256];
    unsigned char decrypted[256];
    char hex[512];
    unsigned char bin[256];

    while (1)
    {

        printf("\nEnter message: ");
        fgets((char *)plaintext, sizeof(plaintext), stdin);

        plaintext[strcspn((char *)plaintext, "\n")] = 0;

        if (strcmp((char *)plaintext, "EXIT") == 0)
            break;

        // ENCRYPT
        int cipher_len = encrypt(plaintext, strlen((char *)plaintext),
                                 key, ciphertext);

        // BIN -> HEX
        to_hex(ciphertext, cipher_len, hex);

        printf("[NETWORK SEND]: %s\n", hex);

        // SIMULATE RECEIVE

        int bin_len = from_hex(hex, bin);

        int dec_len = decrypt(bin, bin_len,
                              key, decrypted);

        decrypted[dec_len] = '\0';

        printf("[NETWORK RECV]: %s\n", decrypted);
    }

    return EXIT_SUCCESS;
} // gcc aes_hex_chat.c -o aes_hex_chat -lssl -lcrypto
/* ./aes_hex_chat

Enter message: Hello World
[NETWORK SEND]: 0C9D4E6B5D444C4B819970780EBCE936
[NETWORK RECV]: Hello World

Enter message: EXIT */