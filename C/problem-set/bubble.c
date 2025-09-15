#define _DEFAULT_SOURCE
#include <stdlib.h>
#include <time.h>
#include <cs50.h>
#include <stdio.h>

void randomize(int array[], int n);
void messy_array(int array[], int n);
void organized(int array[], int n);
void sort_array(int array[], int n);

int main(void)
{
    int n = get_int("how long: ");
    int array[n];
    randomize(array, n);//done
    messy_array(array, n);//done
    organized(array, n);//done (not optimized)
    sort_array(array, n);//done
}

void organized(int array[], int n)
{
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < (n - 1); j++)
        {
            if(array[j + 1] < array[j])
            {
                int temp = array[j];
                array[j] = array[j +1];
                array[j + 1] = temp;
            }
        }
    }
}

void messy_array(int array[], int n)
{
    printf("messy array: ");
    for(int i = 0; i < n; i++)
    {
        printf("%i ", array[i]);
    }
    printf("\n\n");
}

void randomize(int array[], int n)
{
    srandom(time(NULL));
    int m = get_int("max value: ");
    for(int i = 0; i < n; i++)
    {
        array[i] = random() % m;
    }
}

void sort_array(int array[], int n)
{
    printf("organized array: ");
    for(int i = 0; i < n; i++)
    {
        printf("%i", array[i]);
        if(i < n - 1)
        {
            printf(", ");
        }
    }
    printf("\n");
}
