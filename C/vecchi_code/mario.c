#include <stdio.h>
#include <cs50.h>


//introduzione di funzioni
int get_row_int(void);
void row_obstacle(int r);
int get_col_int(void);
void col_obstacle(int c);


//spazio principale
int main(void)
{
    int r = get_row_int();
    row_obstacle(r);
}


//spazio creazione righe x colonne
void row_obstacle(int r)
{
    int c = get_col_int();
    for (int row = 0; row < r; row++)
    {
        col_obstacle(c);
        printf("\n");
    }
}

//spazio creazione colonne
void col_obstacle(int c)
{
     for(int col = 0; col < c; col++)
    {
         printf("#");
    }
}


//quante righe?
int get_row_int (void)
{
    int r = get_int("quante rihe?\n");
    return r;
}


//quante colonne?
int get_col_int(void)
{
    int c = get_int("quante colonne?\n");
    return c;
}
