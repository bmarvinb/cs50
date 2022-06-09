#include <cs50.h>
#include <stdio.h>

void print_padding(int length)
{
    for (int i = 1; i <= length; i++)
    {
        printf("%s", " ");
    }
}

void print_blocks(int length)
{
    for (int i = 1; i <= length; i++)
    {
        printf("%s", "#");
    }
}

void print_delimiter()
{
    printf("%s", "  ");
}

int ask_user_for_height(int min_height)
{
    int height;
    do
    {
        height = get_int("Height: ");
        if (height < min_height)
        {
            printf("Height should be at least %i\n", min_height);
        }
    } while (height < min_height);
    return height;
}

int main(void)
{
    const int MIN_HEIGHT = 1;
    const int height = ask_user_for_height(MIN_HEIGHT);
    for (int i = 1; i <= height; i++)
    {
        print_padding(height - i);
        print_blocks(i);
        print_delimiter();
        print_blocks(i);
        printf("\n");
    }
}