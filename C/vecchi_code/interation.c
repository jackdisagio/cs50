#include<cs50.h>
#include<stdio.h>
#include<string.h>

void draw (int h);

int main(void)
{
    int h = get_int("heigth: ");
    draw(h);
}


void draw(int h)
{
    for(int i = 0; i < h; i++)
    {
        for(int j = 0; j < i + 1; j++)
        {
            printf("#");
        }
        printf("\n");
    }
}
