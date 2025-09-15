#include<cs50.h>
#include<stdio.h>
#include<string.h>

int main(int argc, string argv[])
{
    int n = argc;
    for(int i = 1; i < n; i++)
    {
        int x = strlen(argv[i]);
        for(int j = 0; j < x; j++)
        {
            printf("%c", argv[i][j]);
        }
        printf("\n");
    }
}
