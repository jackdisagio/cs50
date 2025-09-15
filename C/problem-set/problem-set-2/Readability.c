#include<cs50.h>
#include<stdio.h>
#include<string.h>
#include<math.h>


int pfl(char text[], int n);
int calcolo(float parole, float frasi, float lettere);
void risultato(int x);


int main(void)
{
    string text = get_string("text: "); //ciao mi chiamo gacomo.
    int n = strlen(text); //numero di caratteri totali
    int index = pfl(text, n);
    risultato(index);
}


int pfl(char text[], int n)
{
    int parole = 1;
    int frasi = 0;
    int lettere = 0;
    for(int i = 0; i < n; i++)
    {
        switch(text[i])
        {
            case ('.'):
                frasi += 1;
                break;
            case ('!'):
                frasi += 1;
                break;
            case ('?'):
                frasi += 1;
                break;
            case (' '):
                parole += 1;
                break;
            default:
                lettere += 1;
                break;
        }
    }

    float PFL = calcolo(parole, frasi, lettere);
    int index = round(PFL);
    return index;
}


int calcolo(float parole, float frasi, float lettere)
{
    float L = (lettere / parole) * 100;
    float S = (frasi / parole) * 100;
    float idex = 0.0588 * L - 0.296 * S - 15.8;
    return idex;
}


void risultato(int x)
{
    if(x == 0)
    {
        printf("GRADE: less 1");
    }
    else if(x > 16)
    {
        printf("GRADE: 16+");
    }
    else
    {
    printf("GRADE: %i", x);
    }
    printf("\n");
}
