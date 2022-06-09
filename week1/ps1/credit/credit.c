#include <cs50.h>
#include <stdio.h>

long ask_user_for_credit_card_number()
{
    long credit_card_number;
    do
    {
        credit_card_number = get_long("Credit card number: ");
    } while (credit_card_number < 0);
    return credit_card_number;
}

int products(int n)
{
    if (n < 10)
    {
        return n;
    }
    return n % 10 + n / 10;
}

int main(void)
{
    long credit_card_number = ask_user_for_credit_card_number();
    int even_numbers_sum = 0;
    int odd_numbers_sum = 0;
    bool even = true;
    while (credit_card_number > 0)
    {
        int last_number = credit_card_number % 10;
        credit_card_number = credit_card_number / 10;

        if (even)
        {
            odd_numbers_sum += last_number;
        }
        else
        {
            int doubled = last_number * 2;
            even_numbers_sum += products(doubled);
        }
        even = !even;
    }

    int sum = even_numbers_sum + odd_numbers_sum;
    if (sum % 10 == 0)
    {
        printf("Valid card\n");
    }
    else
    {
        printf("Invalid card\n");
    }
}