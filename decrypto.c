#include<cs50.h>
#include<stdio.h>
#include<string.h>

void decripto(string cripto, int key);

int main(void)
{
    int key = get_int("decrypted key: ");
    string cripto = get_string("a message you want to decrypted: ");
    decripto(cripto, key);
}

void decripto(string cripto, int key)
{
    int n = strlen(cripto);
    int c[n];
    for(int i = 0; i < n; i++)
    {
        c[i] = ((cripto[i] - 32 - key) % 95 + 95) % 95 + 32;
    }
    printf("decrypted message: ");
    for(int i = 0; i < n; i++)
    {
        cripto[i] = c[i];
        printf("%c", cripto[i]);
    }
    printf("\n");
}
