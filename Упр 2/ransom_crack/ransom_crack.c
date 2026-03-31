#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// RC4 функция (шифрование и дешифрование одна и та же)
void rc4_crypt(unsigned char *key, int keylen, unsigned char *data, int datalen, unsigned char *output)
{
    unsigned char S[256];
    for(int i = 0; i < 256; i++) S[i] = i;

    int j = 0;
    for(int i = 0; i < 256; i++)
    {
        j = (j + S[i] + key[i % keylen]) % 256;
        unsigned char tmp = S[i];
        S[i] = S[j];
        S[j] = tmp;
    }

    int i = 0;
    j = 0;
    for(int idx = 0; idx < datalen; idx++)
    {
        i = (i + 1) % 256;
        j = (j + S[i]) % 256;
        unsigned char tmp = S[i];
        S[i] = S[j];
        S[j] = tmp;
        unsigned char K = S[(S[i] + S[j]) % 256];
        output[idx] = data[idx] ^ K;
    }
}

int main()
{
    // 1. Криптованное сообщение "Top Secret Data" с ключом "4321"
    unsigned char encrypted[] = {
        0x95, 0x56, 0x93, 0x54, 0x1B, 0x22, 0xCF, 0x6E,
        0xC5, 0x8C, 0x52, 0x34, 0xCC, 0x86, 0x3A
    };
    int len = sizeof(encrypted);

    unsigned char attempt[100]; // буфер для расшифровки
    char key_guess[5]; // "0000" ... "9999" + '\0'

    printf("--- Starting Ransomware Decryptor ---\n");

    for(int i = 0; i <= 9999; i++)
    {
        sprintf(key_guess, "%04d", i); // форматируем с ведущими нулями

        rc4_crypt((unsigned char*)key_guess, 4, encrypted, len, attempt);
        attempt[len] = '\0'; // null-terminator для strstr

        if(strstr((char*)attempt, "Top") != NULL) // ключевое слово для проверки
        {
            printf("[SUCCESS] Key found: %s\n", key_guess);
            printf("Decrypted message: %s\n", attempt);
            break;
        }
    }

    return 0;
}