#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>
#include <string.h>

const int charaters = 26;

typedef struct node
{
    int x;
    struct node* next;
}node;

typedef struct
{
    char c;
    struct node* next;
}arr;

void assign(arr array[]);
void queue(arr array[]);
void trasform(arr array[]);
void free_hash(arr array[]);

int main(void)
{
    arr array[26];
    assign(array);
    queue(array);
    trasform(array);
    free_hash(array);
}

void free_hash(arr array[])
{
    for(int i = 0; i < charaters; i++)
    {
        node *temp = array[i].next;
        array[i].next = NULL;
        free(temp);
    }
}

void trasform(arr array[])
{
    printf("if u wana stop, write: [stop]\n");
    while(true)
    {
        printf("\n");
        char *s = get_string("world: ");
        if(strcmp(s, "end") == 0)
        {
            return;
        }
        int n = strlen(s);
        node *temp = NULL;
        for(int i = 0; i < n; i++)
        {
            for(int j = 0; j < charaters; j++)
            {
                if(s[i] == array[j].c)
                {
                    temp = array[j].next;
                    printf("%i, ", temp->x);
                    continue;
                }
            }
        }
    }
}

void queue(arr array[])
{
    for(int i = 0; i < charaters; i++)
    {
        node *temp = malloc(sizeof(node));
        if(temp == NULL)
        {
            printf("error\n");
            exit(0);
        }
        temp->x = i;
        array[i].next = temp;
        temp->next = NULL;
    }
}

void assign(arr array[])
{
    //creazione array temporale
    char temp[charaters] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};

    for(int i = 0; i < charaters; i++)
    {
        array[i].c = temp[i];
    }
}
