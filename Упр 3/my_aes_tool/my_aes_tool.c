#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>

void handleErrors()
{
    printf("OpenSSL error\n");
    exit(1);
}

unsigned char *read_file(const char *filename, long *len)
{
    FILE *f = fopen(filename, "rb");
    if (!f)
    {
        perror("file");
        exit(1);
    }

    fseek(f, 0, SEEK_END);
    *len = ftell(f);
    rewind(f);

    unsigned char *data = malloc(*len);
    fread(data, 1, *len, f);
    fclose(f);

    return data;
}

void write_file(const char *filename, unsigned char *data, int len)
{
    FILE *f = fopen(filename, "wb");
    fwrite(data, 1, len, f);
    fclose(f);
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

int main(int argc, char *argv[])
{

    if (argc != 5)
    {
        printf("Usage: %s [enc|dec] input output key\n", argv[0]);
        return 1;
    }

    char *mode = argv[1];
    char *input_file = argv[2];
    char *output_file = argv[3];
    char *key_str = argv[4];

    // key (16 bytes)
    unsigned char key[16];
    memset(key, 0, 16);
    strncpy((char *)key, key_str, 16);

    long inlen;
    unsigned char *input = read_file(input_file, &inlen);

    unsigned char *output = malloc(inlen + 16); // padding safety

    int outlen;

    if (strcmp(mode, "enc") == 0)
    {
        outlen = encrypt(input, inlen, key, output);
    }
    else if (strcmp(mode, "dec") == 0)
    {
        outlen = decrypt(input, inlen, key, output);
    }
    else
    {
        printf("Invalid mode\n");
        return 1;
    }

    write_file(output_file, output, outlen);

    printf("Done. Output bytes: %d\n", outlen);

    free(input);
    free(output);

    return EXIT_SUCCESS;
} // gcc my_aes_tool.c -o my_aes_tool -lssl -lcrypto
// ./my_aes_tool enc plain.txt cipher.bin key1234567890123
// xxd cipher.bin
// ./my_aes_tool dec cipher.bin result.txt key1234567890123