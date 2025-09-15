// Implements a dictionary's functionality
#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "dictionary.h"


typedef struct node
{
    char array[LENGTH];
    struct node *next;
} node;

const unsigned int N = (26 * 26) + 1;

node *table[N] = {NULL};
int k = 0;
int cord = 0;

void allocate_hash(char array[], int c);
void singolar_unload(node *temp);

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    if(word[1] == '\0' || !isalpha(word[1])){cord = 676;}
    else
    {
        cord = (((word[0] - 'a') * 26) + (word[1] - 'a'));
    }

    node *temp = table[cord];
    while(temp != NULL)
    {
        if(!strcmp(word, temp->array)){return true;}
        temp = temp->next;
    }
    return false;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    FILE *vocabulary = fopen(dictionary, "r");
    if(vocabulary == NULL)
    {
        return false;
    }

    fseek(vocabulary, 0, SEEK_END);
    int length = ftell(vocabulary);
    fseek(vocabulary, 0, SEEK_SET);

    char *temp = malloc((sizeof(char) * length));
    fread(temp, sizeof(char), length, vocabulary);
    fclose(vocabulary);

    int c = 0;
    char Atemp[LENGTH];
    for(int i = 0; i < length; i++)
    {
        c = 0;
        while(temp[i] != '\n')
        {
            Atemp[c] = tolower(temp[i]);
            c++;
            i++;
        }
        Atemp[c] = '\0';
        allocate_hash(Atemp, c);
        k++;
    }
    free(temp);
    return true;
}

void allocate_hash(char Atemp[], int c)
{
    node *n = malloc(sizeof(node));
    if(n == NULL)
    {
        printf("error");
        exit(0);
    }

    if(Atemp[1] == '\0' || !isalpha(Atemp[1]))
    {
        cord = 676;
    }
    else
    {
        cord = (((Atemp[0] - 'a') * 26) + (Atemp[1] - 'a'));
    }

    strcpy(n->array, Atemp);
    n->next = NULL;
    if(table[cord] == NULL)
    {
         table[cord] = n;
    }
    else
    {
        node *temp = table[cord];
        table[cord] = n;
        n->next = temp;
    }
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    if(k == 0){return 0;}
    return k;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for(int i = 0; i < 677; i++)
    {
        if(table[i] == NULL)
        {
            continue;
        }
        else
        {
            node *temp = table[i];
            singolar_unload(temp);
        }
        table[i] = NULL;
    }
    return true;
}

void singolar_unload(node *temp)
{
    if(temp == NULL){return;}
    singolar_unload(temp->next);
    free(temp);
}
