#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>

void adapt(string text, int n);
int tot_count(string text, int n, int Nletter[], char letter[]);
void single_count(int Nletter[], char letter[], char dd[]);
void draw(int o, char letter[], int Nletter[], int n, char dd[]);

int main(void)
{
    string text = get_string("text to analyze: ");
    int n = strlen(text);
    char letter[26] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
    int Nletter[26] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    adapt(text, n);
    int o = tot_count(text, n, Nletter, letter);
    char dd[26];
    single_count(Nletter, letter, dd);
    draw(o, letter, Nletter, n, dd);
}

void draw(int o, char letter[], int Nletter[], int n, char dd[])
{
    int i = 0;
    printf("lettere più frequenti: ");
    while(dd[i] != '\0')
    {
        printf("%c ", dd[i]);
        i++;
    }
    printf("\nlettere totali: %i\n", o);
    printf("non lettere: %i\n", (n - o));
    char yn = tolower(get_char("vuoi vedere il n. di ogni lettera? y/n: "));
    if(yn == 'y')
    {
        printf("\n");
        for(int j = 0; j < 26; j++)
        {
            printf("lettera %c: %i\n", letter[j], Nletter[j]);
        }
    }
    else
    {
        return;
    }
}

void single_count(int Nletter[], char letter[], char dd[])
{
    int upper = 0;
    int k = 0;
    int temp = 0;
    for(int i = 0; i < 26; i++)
    {
        if(Nletter[i] > upper)
        {
            upper = Nletter[i];
            temp = i;
        }
    }
    dd[k] = letter[temp];
    for(int i = 0; i < 26; i++)
    {
        if(i == temp)
        {
            continue;
        }
        else if(Nletter[i] == upper)
        {
            k++;
            dd[k] = letter[i];
        }
    }
}

int tot_count(string text, int n, int Nletter[], char letter[])
{
    int o = 0;
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < 26; j++)
        {
            if(text[i] == letter[j])
            {
                o++;
                (Nletter[j])++;
            }
        }
    }
    return o;
}

void adapt(string text, int n)
{
    for(int i = 0; i < n; i++)
    {
        text[i] = tolower(text[i]);
    }
}
