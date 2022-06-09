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

bool only_alphabet(string s)
{
    bool all_alphabet = true;
    for (int i = 0; i < strlen(s); i++)
    {
        if (!isalpha(s[i]))
        {
            all_alphabet = false;
        }
    }
    return all_alphabet;
}

char rotate(char c, string key)
{
    if (isupper(c))
    {
        int order = (int)c - 65;
        return toupper(key[order]);
    }
    int order = (int)toupper(c) - 65;
    return tolower(key[order]);
}

int main(int argc, string argv[])
{
    string key = argv[1];
    if (!key || !only_alphabet(key))
    {
        printf("Usage: ./substitution key\n");
    }
    else if (strlen(key) < 26)
    {
        printf("Key must contain 26 characters.\n");
    }
    else
    {
        string text = get_text();

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