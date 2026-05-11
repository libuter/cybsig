#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <openssl/evp.h>
#include <time.h>

#define DB_FILE "users.db"

void sha256(const char *input, unsigned char *output, unsigned int *len)
{

    EVP_MD_CTX *ctx = EVP_MD_CTX_new();

    EVP_DigestInit_ex(ctx, EVP_sha256(), NULL);
    EVP_DigestUpdate(ctx, input, strlen(input));
    EVP_DigestFinal_ex(ctx, output, len);

    EVP_MD_CTX_free(ctx);
}

void to_hex(unsigned char *in, int len, char *out)
{
    for (int i = 0; i < len; i++)
    {
        sprintf(out + i * 2, "%02x", in[i]);
    }
    out[len * 2] = '\0';
}

void generate_salt(char *salt)
{

    unsigned char bytes[4];

    for (int i = 0; i < 4; i++)
    {
        bytes[i] = rand() % 256;
    }

    for (int i = 0; i < 4; i++)
    {
        sprintf(salt + i * 2, "%02x", bytes[i]);
    }

    salt[8] = '\0';
}

void register_user()
{

    char username[50];
    char password[50];
    char salt[9];

    unsigned char hash[EVP_MAX_MD_SIZE];
    unsigned int hash_len;

    char final_input[150];
    char hash_hex[65];

    printf("Username: ");
    scanf("%s", username);

    printf("Password: ");
    scanf("%s", password);

    generate_salt(salt);

    // salt + password
    strcpy(final_input, salt);
    strcat(final_input, password);

    sha256(final_input, hash, &hash_len);
    to_hex(hash, hash_len, hash_hex);

    FILE *f = fopen(DB_FILE, "a");

    fprintf(f, "%s:%s:%s\n", username, salt, hash_hex);

    fclose(f);

    printf("User registered!\n");
}

void login_user()
{

    char username[50];
    char password[50];

    printf("Username: ");
    scanf("%s", username);

    printf("Password: ");
    scanf("%s", password);

    FILE *f = fopen(DB_FILE, "r");

    if (!f)
    {
        printf("DB not found\n");
        return;
    }

    char file_user[50], salt[20], stored_hash[70];

    char line[200];

    unsigned char hash[EVP_MAX_MD_SIZE];
    unsigned int hash_len;

    char input[150];
    char computed[65];

    while (fgets(line, sizeof(line), f))
    {

        sscanf(line, "%[^:]:%[^:]:%s", file_user, salt, stored_hash);

        if (strcmp(username, file_user) == 0)
        {

            strcpy(input, salt);
            strcat(input, password);

            sha256(input, hash, &hash_len);
            to_hex(hash, hash_len, computed);

            if (strcmp(computed, stored_hash) == 0)
            {
                printf("LOGIN SUCCESSFUL!\n");
            }
            else
            {
                printf("WRONG PASSWORD!\n");
            }

            fclose(f);
            return;
        }
    }

    printf("User not found\n");
    fclose(f);
}

int main()
{

    srand(time(NULL));

    int choice;

    while (1)
    {

        printf("\n1. Register\n2. Login\n3. Exit\nChoice: ");
        scanf("%d", &choice);

        if (choice == 1)
            register_user();
        else if (choice == 2)
            login_user();
        else
            break;
    }

    return EXIT_SUCCESS;
} // gcc shadow.c -o shadow -lssl -lcrypto
/* 1. Register
2. Login
3. Exit
Choice: 1
Username: test
Password: 1234
User registered!

1. Register
2. Login
3. Exit
Choice: 2
Username: test
Password: 1234
LOGIN SUCCESSFUL!

1. Register
2. Login
3. Exit
Choice: 3*/