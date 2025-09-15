#define _DEFAULT_SOURCE
#include <stdlib.h>
#include <time.h>
#include <cs50.h>
#include <stdio.h>

void randomize(int array[], int n);
void messy_array(int array[], int n);
void order(int array[], int n);
void sort_array(int array[], int n);

int main(void)
{
    int n = get_int("how long: ");
    int array[n];
    randomize(array, n);
    messy_array(array, n);
    order(array, n);
    sort_array(array, n);
}

void sort_array(int array[], int n)
{
    printf("sort array: ");
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

void order(int array[], int n)
{
    for(int i = 0; i < n - 1; i++)
    {
        int less = array[i];
        int k = i;
        for(int j = i + 1; j < n; j++)
        {
            if(less > array[j])
            {
                less = array[j];
                k = j;
            }
        }
        if(k > i)
        {
            int temp = array[i];
            array[i] = array[k];
            array[k] = temp;
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
    int m = get_int("max value: ");
    srandom(time(NULL));
    for(int i = 0; i < n; i++)
    {
        array[i] = random() % m;
    }
}
