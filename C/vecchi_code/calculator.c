#include <cs50.h>
#include <stdio.h>


int main(void)
{
    long dollars = 1;
    while(true)
    {
        char $ = get_char("hai $%li, voi radoppire e passarlo alla prossima persona? ", dollars);
        if ($ == 'y')
        {
            dollars *= 2;
        }
        else
        {
            printf("hai ottenuto $%li\n", dollars);
            break;
        }
    }
}
