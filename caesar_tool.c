#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

char caesar_char(char symbol, int key, int encrypt)
{
    if (isupper(symbol))
    {
        if (encrypt)
            return((symbol - 'A' + key) % 26) + 'A';
        else
            return((symbol - 'A' - key + 26) % 26) + 'A';
    } 
    else if (islower(symbol))
    {
        if (encrypt)
            return ((symbol - 'a' + key) % 26) + 'a';
        else
            return((symbol - 'a' - key + 26) % 26) + 'a';
    }
    return symbol;
}

int main(int argc, char **argv)
{
    if (argc != 5){
        printf("Usage:\n  %s -e|-d input.txt key.txt output.txt\n", argv[0]);
        return EXIT_FAILURE;
    }

    int encrypt = 0;
    if (strcmp(argv[1], "-e") == 0) encrypt = 1;
    else if (strcmp(argv[1], "-d") == 0) encrypt = 0;
    else{
        printf("Unknown option %s\n", argv[1]);
        return EXIT_FAILURE;
    }

    char *input_file = argv[2];
    char *key_file = argv[3];
    char *output_file = argv[4];

    FILE *kf = fopen(key_file, "r");
    if (!kf)
    {
        perror("Cannot open key file");
        return EXIT_FAILURE;
    }
    int key;
    if (fscanf(kf, "%d", &key) != 1)
    {
        perror("Invalid key file");
        fclose(kf);
        return EXIT_FAILURE;
    }
    fclose(kf);

    FILE *fin = fopen(input_file, "r");
    if (!fin)
    {
        perror("Cannot open input file");
        return EXIT_FAILURE;
    }
    FILE *fout = fopen(output_file, "w");
    if (!fout)
    {
        perror("Cannot open output file");
        fclose(fin);
        return EXIT_FAILURE;
    }

    int ch;
    while((ch = fgetc(fin)) != EOF)
    {
        fputc(caesar_char((char)ch, key, encrypt), fout);
    }

    fclose(fin);
    fclose(fout);

    printf("Operation %s completed successfully!\n", encrypt ? "encryption" : "decryption");
    return EXIT_SUCCESS;
}
