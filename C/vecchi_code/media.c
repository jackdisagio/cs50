#include<cs50.h>
#include<stdio.h>

//intro
float media(int lunghezza, int vettore[]);

//main
int main(void)
{
    int valori = get_int("numero di valori: ");
    int scores[valori];
    for(int i = 0; i < valori; i++)
    {
        scores[i] = get_int("valore %i: ", i + 1);
    }

    printf("media: %f\n", media(valori, scores) );
}

//calcolo media
float media(int lunghezza, int vettore[]) //le [] dopo "vettore" indicano al sistema che quella funzione ("vettore") è un array
{
    int sum = 0;
    for(int i = 0; i < lunghezza; i++)
    {
        sum += vettore[i];
    }
    return sum / (float) lunghezza;
}
