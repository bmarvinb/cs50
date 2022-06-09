#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

string get_text()
{
    string text;
    do
    {
        text = get_string("plaintext: ");
    } while (strlen(text) < 0);
    return text;
}

bool only_digits(string s)
{
    bool all_digits = true;
    for (int i = 0; i < strlen(s); i++)
    {
        if (!isdigit(s[i]))
        {
            all_digits = false;
        }
    }
    return all_digits;
}

int get_padding(char c)
{
    if (isupper(c))
    {
        return 65;
    }

    return 97;
}

int rotate(char c, int key)
{
    int padding = get_padding(c);
    int code = (int)c - padding + key;
    return code % 26 + padding;
}

int main(int argc, string argv[])
{
    string key = argv[1] if (!key || !only_digits(key))
    {
        printf("Usage: ./caesar key\n");
    }
    else
    {
        string text = get_text();
        int key = atoi(key);

        printf("ciphertext: ");
        for (int i = 0; i < strlen(text); i++)
        {
            if (isalpha(text[i]))
            {
                printf("%c", rotate(text[i], key));
            }
            else
            {
                printf("%c", text[i]);
            }
        }
        printf("\n");
    }
}
