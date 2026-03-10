#include <stdio.h>
#include <stdlib.h>

long get_file_size(FILE *f){
    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    rewind(f);
    return size;
}

int main(int argc, char **argv){
    if(argc != 4){
        printf("Usage: %s input_file key_file output_file\n", argv[0]);
        return EXIT_FAILURE;
    }

    FILE *input = fopen(argv[1], "rb");
    FILE *key = fopen(argv[2], "rb");
    FILE *output = fopen(argv[3], "wb");

    if (!input || !key || !output){
        perror("File error");
        return EXIT_FAILURE;
    }

    long input_size = get_file_size(input);
    long key_size = get_file_size(key);

    if (key_size < input_size){
        printf("Error: Key is shorter than input file!\n");
        return EXIT_FAILURE;
    }

    int in_byte, key_byte;

    while((in_byte = fgetc(input)) != EOF){
        key_byte = fgetc(key);
        unsigned char encrypted = in_byte ^ key_byte;
        fputc(encrypted, output);
    }

    fclose(input);
    fclose(key);
    fclose(output);

    printf("Operation completed.\n");
    return EXIT_SUCCESS;
}