#define _DEFAULT_SOURCE
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

typedef struct person
{
    char allel[2];
    struct person *parent[2];
}person;

char allel_sign(void);
person *create_family(int generation);
void print_family(person *start, int generation);
void free_family(person *start);

const int GENERATION = 3;
const int INDENT_LENGTH = 4;

int main(void)
{
    srandom(time(NULL));

    person *start = create_family(GENERATION);
    print_family(start, 0);//done

    free_family(start);
}

void free_family(person *start)
{
    if(start == NULL)
    {
        return;
    }

    for(int i = 0; i < 2; i++)
    {
        free_family(start->parent[i]);
    }

    free(start);
}

void print_family(person *start, int generation)
{
    // Handle base case
    if (start == NULL)
    {
        return;
    }

    // Print indentation
    for (int i = 0; i < generation * INDENT_LENGTH; i++)
    {
        printf(" ");
    }

    // Print person
    if (generation == 0)
    {
        printf("Child (Generation %i): blood type %c%c\n", generation, start->allel[0], start->allel[1]);
    }
    else if (generation == 1)
    {
        printf("Parent (Generation %i): blood type %c%c\n", generation, start->allel[0], start->allel[1]);
    }
    else
    {
        for (int i = 0; i < generation - 2; i++)
        {
            printf("Great-");
        }
        printf("Grandparent (Generation %i): blood type %c%c\n", generation, start->allel[0], start->allel[1]);
    }

    // Print parents of current generation
    print_family(start->parent[0], generation + 1);
    print_family(start->parent[1], generation + 1);
}

person *create_family(int generation)
{
    if(generation == 0)
    {
        return NULL;
    }

    person *n = malloc(sizeof(person));
    if(n == NULL)
    {
        printf("error\n");
        exit(0);
    }

    for(int i = 0; i < 2; i++)
    {
        n->parent[i] = create_family(generation - 1);
    }

    for(int i = 0; i < 2; i++)
    {
        if(n->parent[i] == NULL)
        {
            n->allel[i] = allel_sign();
        }
        else
        {
            n->allel[i] = n->parent[i]->allel[(random() % 2)];
        }
    }

    return n;
}

char allel_sign(void)
{
    int n = random() % 3;
    char x = 'x';

    switch(n)
    {
        case 1:
        {
            x = 'A';
            break;
        }
        case 2:
        {
            x = 'B';
            break;
        }
        default:
        {
            x = 'O';
            break;
        }
    }
    return x;
}
