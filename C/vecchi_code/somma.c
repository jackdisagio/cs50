#include<cs50.h>
#include<stdio.h>

int somma(int valori, int numeri[]);

int main(void)
{
    int valori = get_int("quanti valori: ");
    int numeri[valori]; //array
    for(int i = 0; i < valori; i++)
    {
        numeri[i] = get_int("valore %i: ", i + 1); //assegnazione dei valori all'array
    }

    printf("somma: %i\n", somma(valori, numeri));
}

int somma (int valori, int numeri[])
{
    int sum = 0;
    for(int i = 0; i < valori; i++)
    {
        sum += numeri[i];
    }
    return sum;
}
