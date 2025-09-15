#include<cs50.h>
#include<stdio.h>
#include<ctype.h>
#include<string.h>

int player1(void);
int player2(void);
int associazione(char p[], int n);
void vincitore(int tot1, int tot2);

int main (void)
{
    int tot1 = player1();
    int tot2 = player2();
    vincitore(tot1, tot2);
}


int player1(void)
{
    string p1 = get_string("parola giocatore 1: "); //creazione dell'array 1
    int n1 = strlen(p1); //presa lunghezza dell'array 1
    int tot1 = associazione(p1, n1); //associazione dell'array 1
    return tot1;
}

int player2(void)
{
    string p2 = get_string("parola giocatore 2: ");
    int n2 = strlen(p2);
    int tot2 = associazione(p2, n2);
    return tot2;
}


int associazione(char p[], int n)
{
    int tot = 0; //valore dove viene aggiunto periodicamente il singolo valore dell'array "sum"
    char lettere[26] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J','K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'Z'};
    int valori[26] = {1, 3, 3, 2, 1, 4,	2, 4, 1, 8,	5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};
    for(int i = 0; i < n; i++) //loop per la lunghezza del messaggio
    {
        p[i] = toupper(p[i]);
        for(int a = 0; a < 26; a++) //loopper le possibili letteree numeri
        {
            if(p[i] == lettere[a])
            {
                 tot += valori[a];
            }
            else
            {
                tot += 0;
            }
        }
    }
    return tot;
}


void vincitore(int tot1, int tot2)
{
    if(tot1 > tot2)
    {
        printf("giocatore 1 vince con un punteggio di: %i", tot1);
    }
    else if(tot1 < tot2)
    {
        printf("giocatore 2 vince con un punteggio di: %i", tot2);
    }
    else if(tot1 == tot2)
    {
        printf("i giocatori hanno pareggiato, con un punteggio di: %i", tot1);
    }
    printf("\n");
}
