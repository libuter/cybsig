#include <stdio.h>
#include <ctype.h>
#include <string.h>

int analyze_password(const char *pass)
{
    int score = 0;
    int has_lower = 0, has_upper = 0, has_digit = 0, has_special = 0;

    char *weak[] = {"password", "123456", "admin", "qwerty"};
    int weak_count = sizeof(weak) / sizeof(weak[0]);

    int len = strlen(pass);
    score += len; // +1 за каждый символ

    for (int i = 0; i < len; i++)
    {
        if (islower(pass[i]))
            has_lower = 1;
        else if (isupper(pass[i]))
            has_upper = 1;
        else if (isdigit(pass[i]))
            has_digit = 1;
        else
            has_special = 1;
    }

    if (has_lower)
        score += 10;
    if (has_upper)
        score += 10;
    if (has_digit)
        score += 15;
    if (has_special)
        score += 20;

    // Проверка на слабый пароль
    for (int i = 0; i < weak_count; i++)
    {
        if (strcmp(pass, weak[i]) == 0)
        {
            score -= 20;
            break;
        }
    }

    if (score < 0)
        score = 0;
    if (score > 100)
        score = 100;

    return score;
}

int main()
{
    char password[100];
    printf("Enter password: ");
    scanf("%s", password);

    int score = analyze_password(password);
    printf("Password strength: %d/100\n", score);

    return 0;
}