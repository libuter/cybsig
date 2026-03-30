#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXN 1000

int main()
{
    char text[MAXN] = "THISISATESTMESSAGETHISISATESTMESSAGE";

    int len = strlen(text);

    printf("--- KASISKI ANALYSIS ---\n");

    for (int i = 0; i < len - 2; i++)
    {

        char trigram[4];
        trigram[0] = text[i];
        trigram[1] = text[i + 1];
        trigram[2] = text[i + 2];
        trigram[3] = '\0';

        for (int j = i + 1; j < len - 2; j++)
        {

            if (strncmp(trigram, &text[j], 3) == 0)
            {
                int distance = j - i;

                printf("Found \"%s\": Pos %d & Pos %d -> Distance: %d\n",
                       trigram, i, j, distance);
            }
        }
    }

    return 0;
}