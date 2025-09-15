#include<stdio.h>
#include<cs50.h>

void print_col(int height);

int main(void)
{
    int h = get_int("height: ");
    print_col(h);
}


void print_col(int height)
{
    for (int i = 0; i < height; i++)
    {
        printf("#\n");
    }
}
