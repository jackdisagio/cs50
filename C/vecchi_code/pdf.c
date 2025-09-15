#include <cs50.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

typedef uint8_t x;

int main(int argc, char *argv[])
{
    if(argc != 2)
    {
        printf("use: %s input file\n", argv[0]);
        return 0;
    }

    FILE *pdf = fopen(argv[1], "rb"); //read binary
    if(pdf == NULL)
    {
        printf("file %s not found\n", argv[1]);
        return 0;
    }

    string text = get_string("text: ");
    int l = strlen(text);

    x tx[l]; // 1 byte x lunghezza

    int s = 0;
    for(int i = 0; i < l; i++)
    {
        fread(&tx[i], sizeof(tx[i]), 1, pdf);
        if(text[i] == tx[i])
        {
            s++;
        }
    }

    if(s == l)
    {
        printf("the text is in the file\n");
    }
    else
    {
        printf("the text isn't in the file\n");
    }

    fclose(pdf);
}
