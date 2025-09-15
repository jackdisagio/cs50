#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>

typedef struct node
{
    int number;
    struct node *next;
}node;

int main(void)
{
    node *start = NULL;
    int count = 0;

    for(int i = 0; i < 3; i++)
    {
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            for(int j = 0; j < count; j++)
            {
                
            }
            return 1;
        }
        n->number = get_int("number: ");
        n->next = NULL;

        if(start == NULL)//solo primo nodo
        {
            start = n;
        }
        else //restanti nodi
        {
            node *temp = start; //temp ora punta al primo nodo (come lo start)

            while(temp->next != NULL) //loop finche il next != NULL
            {
                temp = temp->next; //temp avanza nodo->nodo->nodo, finche il ciclo è attivo (next != NULL)
            }
            temp->next = n; //a questo temp, che è al nodo con next == NULL gli vine eassegnato l'indirizzo dell'n appena creato
        }
        count++;
    }

    //time passes

    node *prt = start;
    printf("%i\n", start->number);
    free(start);
    while(prt != NULL) //fino all'ultimo
    {
        node *temp = prt;
        printf("%i\n", temp->number);
        prt = prt->next;

        free(prt); //il comando free può liberare solamente un malloc alla volta
    }
    return 0;
}
