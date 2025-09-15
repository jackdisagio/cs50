#include <cs50.h>
#include <stdio.h>

//intro
int altezza(void);
void loop(void);

//main function
int main(void)
{
    loop();
}

//altezza
int altezza(void)
{
    int h;
    do
    {
        h = get_int("altezza (0 > h > 10): ");
    }
    while (h < 1 || h > 10);
    return h;
}

//loop
void loop(void)
{
    int h = altezza();
    char simbolo = get_char("con quale simbolo? ");
    int s;
    s = h - 1;
    int b;
    b = -s + h;
    for(int row = 0; row < h; row++)
    {
        for (int space = 0; space < s; space++)
        {
            printf(" ");
        }
        for (int block = 0; block < b; block++)
        {
            printf("%c", simbolo);
        }
        printf("\n");
        s = s - 1;
        b = b + 1;
    }
}
