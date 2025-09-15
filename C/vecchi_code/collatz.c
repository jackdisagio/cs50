#include <cs50.h>
#include <stdio.h>

int collatz(int n);

int main(void)
{
    int n = get_int("give me a number for collatz: ");
    printf("passaggi: %i\n", collatz(n));
}

int collatz(int n)
{
    if(n == 1)
    {
        return 0;
    }
    else if((n % 2) == 0)
    {
        n = n/2;
        printf("%i / 2 = %i\n", n/2, n);
        return 1 + collatz(n);
    }
    else
    {
        n = (3 * n) + 1;
        printf("3(%i) + 1 = %i\n", (n - 1) / 3, n);
        return 1 + collatz(n);
    }
}
