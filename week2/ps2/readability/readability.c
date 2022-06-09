#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

string get_text()
{
    string text;
    do
    {
        text = get_string("Text: ");
    } while (strlen(text) < 0);
    return text;
}

double calculate_by_coleman_formula(double l, double s)
{
    return 0.0588 * l - 0.296 * s - 15.8;
}

double calculate_average(int n, int m)
{
    return (((double)n / (double)m) * 100);
}

bool is_end_of_the_sentence(char s)
{
    const int DOT = 46;
    const int QUESTION = 63;
    const int EXCLAMATION_POINT = 33;
    int n = (int)s;
    return n == DOT || n == QUESTION || n == EXCLAMATION_POINT;
}

int calculate_grade(string text)
{
    int letters = 0;
    int sentences = 0;
    int words = 0;
    for (int i = 0; i < strlen(text); i++)
    {
        if (isalpha(text[i]))
        {
            letters += 1;
        }
        else if (isspace(text[i]) || !text[i + 1])
        {
            words += 1;
        }
        else if (is_end_of_the_sentence(text[i]))
        {
            if (words == 0)
            {
                words += 1;
            }
            sentences += 1;
        }
    }

    double average_letters = calculate_average(letters, words);
    double average_sentences = calculate_average(sentences, words);
    double result = (int)calculate_by_coleman_formula(average_letters, average_sentences);

    return result;
}

int main(void)
{
    string text = get_text();
    int grade = calculate_grade(text);

    if (grade < 1)
    {
        printf("Before grade 1\n");
    }
    else if (grade <= 16)
    {
        printf("Grade: %i\n", grade);
    }
    else
    {
        printf("Grade: 16+\n");
    }
}
