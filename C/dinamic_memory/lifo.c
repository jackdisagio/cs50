#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>

typedef struct node
{
    int number;
    struct node *next;
}node;

int main(void)
{
    node *start;

    for(int i = 0; i < 3; i++)
    {
        node *n = malloc(sizeof(node));
        if(n == NULL)
        {
            return 0;
        }
        n->number = get_int("number: ");

        n->next = start;

        start = n;
    }

    //time passes

    node *ptr = start;
    while(ptr != NULL)
    {
        node *temp = ptr;
        printf("%i\n", ptr->number);
        ptr = ptr->next;

        free(temp);//il comando free può liberare solamente un malloc alla volta
    }
}
