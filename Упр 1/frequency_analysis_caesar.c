#include <stdio.h>
#include <ctype.h>
#include <string.h>

void print_histogram(const char *text)
{
    int counts[26] = {0};
    int total_letters = 0;

    for (int i = 0; text[i] != '\0'; i++)
    {
        if (isalpha(text[i]))
        {
            char upper = toupper(text[i]);
            int index = upper - 'A';
            counts[index]++;
            total_letters++;
        }
    }

    printf("\n--- FREQUENCY HISTOGRAM ---\n");

    for (int i = 0; i < 26; i++)
    {
        if (counts[i] > 0)
        {
            printf("%c (%3d): ", 'A' + i, counts[i]);

            for (int j = 0; j < counts[i]; j++)
            {
                printf("*");
            }

            printf("\n");
        }
    }

    printf("\nTotal letters: %d\n", total_letters);
}

int main()
{
    char text[] = "Sample text refers to placeholder content used to demonstrate or preview design, format, or functionality before the final content is added. It is often generic and doesn’t carry any significant meaning. One of the most commonly used forms of sample text is Lorem Ipsum, a pseudo-Latin text that has been in use since the 1500s.";

    print_histogram(text);

    return 0;
}
