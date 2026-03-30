#include <stdio.h>
#include<stdlib.h>
#include <ctype.h>

char caesar_encrypt_char(char p, int k)
{
    if (isupper(p)){
        return((p - 'A' + k) % 26) + 'A';
    } else if (islower(p)){
        return((p - 'a' + k) % 26) + 'a';
    }
    return p;
}

char caesar_decrypt_char(char c, int k)
{
    if (isupper(c)){
        return((c - 'A' - k + 26) % 26) + 'A';
    } else if (islower(c)) {
        return((c - 'a' - k + 26) % 26) + 'a';
    }
    return c;
}

void caesar_encrypt_string(char *text, int k)
{
    for (int i = 0; text[i] != '\0'; i++)
    {
        text[i] = caesar_encrypt_char(text[i], k);
    }
}

void caesar_decrypt_string(char *text, int k)
{
    for (int i = 0; text[i] != '\0'; i++)
    {
        text[i] = caesar_decrypt_char(text[i], k);
    }
}

int main()
{
    char text[] = "HELLO";
    int key = 3;

    caesar_encrypt_string(text, key);
    printf("Encrypted: %s\n", text); 

    caesar_decrypt_string(text, key);
    printf("Decrypted: %s\n", text);

    char bonus[] = "Hello, World!";
    caesar_encrypt_string(bonus, key);
    printf("Encrypted bonus: %s\n", bonus);
    caesar_decrypt_string(bonus, key);
    printf("Decrypted bonus: %s\n", bonus);

    return EXIT_SUCCESS;
}
