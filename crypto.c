#include<cs50.h>
#include<stdio.h>
#include<string.h>


void convert(string s, int key);

int main(void)
{
    int key = get_int("endcrypt key: ");
    string question = get_string("a message you want to encrypt: ");
    convert(question, key);
}


void convert(string s, int crt)
{
    int n = strlen(s);
    int valori[n];
    for(int i = 0; i < n; i++)
    {
        valori [i] = ((s[i] - 32 + crt) % 95 + 95) % 95 + 32;
    }
    printf("encrypt message: ");
    for(int i = 0; i < n; i++)
    {
        s[i] = valori[i];
        printf("%c", s[i]);
    }
    printf("\n");
}
