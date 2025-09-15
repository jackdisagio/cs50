#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

void agree();

int main(void)
{
    agree();
}

void agree()
{
    char x = 'x';
    printf("do you agree? ");
    scanf("%c", &x);
    if(tolower(x) == 'y'){printf("agree\n");}
    else if(tolower(x) == 'n'){printf("desagree\n");}
    else{agree();}
}
