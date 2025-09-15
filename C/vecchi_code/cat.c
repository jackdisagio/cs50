#include <cs50.h>
#include <stdio.h>

int get_positive_int(void);
void cat(int n);

//funzione principale del programma
int main(void)
{
    int times = get_positive_int();
    cat(times); //righa che porta il valore n al di fuori della main function
}

//creazone spazio di ripetizione
int get_positive_int(void)
{
    int n;
    do
    {
        n = get_int("quanti gatti ci sono nella stanza?\n");
    }
    while(n < 0);
    return n;
}

//creazione spazio cat
void cat(int n)
{
    for(int i = 0; i < n; i++)
    {
        printf("meow\n");
    }
}
