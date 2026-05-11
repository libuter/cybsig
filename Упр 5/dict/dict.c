#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <crypt.h>

void dictionary_attack(const char *target_hash, const char *dict_file)
{
    FILE *file = fopen(dict_file, "r");

    if (!file)
    {
        printf("File error!\n");
        return;
    }

    char word[256];

    printf("--- Dictionary Attack ---\n");

    while (fgets(word, sizeof(word), file))
    {
        word[strcspn(word, "\n")] = 0;

        char *computed_hash = crypt(word, target_hash);

        if (strcmp(computed_hash, target_hash) == 0)
        {
            printf("[FOUND] Password: %s\n", word);
            fclose(file);
            return;
        }
        printf("TRY: %s\n", word);
    }

    printf("[NOT FOUND]\n");
    fclose(file);
}

int main()
{
    char hash[] =
        "$6$salt$IY9X7hQTQQDKsFQu/uJhXrVtc0SV.8wk9Ni5Je6sjSu8uieQ1uklcKdMqraAviWyu0EU4/jjpga.kfr7uxjQK1";

    dictionary_attack(hash, "rockyou_mini.txt");

    return EXIT_SUCCESS;
} // gcc dict.c -o dict -lcrypt
// cat -A rockyou_mini.txt
// sed -i 's/\r$//' rockyou_mini.txt
// ./dict