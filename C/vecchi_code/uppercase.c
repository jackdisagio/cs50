#include<cs50.h>
#include<stdio.h>
#include<string.h>
#include<ctype.h>

int main(void)
{
    string prima = get_string("prima: ");
    printf("dopo: ");
    int n = strlen(prima);
    for(int i = 0; i < n; i++)
    {
        printf("%c", toupper(prima[i]));
    }
    printf("\n");
}
