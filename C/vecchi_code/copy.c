#include <stdio.h>
#include <stdint.h>

typedef uint8_t BYTE; //(alias): 8 bit, 1 byte

int main(int argc, char *argv[])
{
    if(argc != 3)
    {
        printf("use: %s surce destination\n", argv[0]);
        return 0;
    }

    FILE *src = fopen(argv[1], "rb");
    if(src == NULL)
    {
        printf("the file %s dosn't exist\n", argv[1]);
        return 0;
    }

    FILE *dst = fopen(argv[2], "wb");
    if(dst == NULL)
    {
        printf("the file %s dosn't exist\n", argv[2]);
        return 0;
    }

    BYTE b;

    while (fread(&b, sizeof(b), 1, src) != 0) //assegnazione di 1 byte a b, (se non gli viene assegnato è = 0 e non chiama più un'altro ciclo)
    {
        fwrite(&b, sizeof(b), 1, dst); //asseganzione al file di destinazione (dst) di 1 byte (preso da b)
    }

    //chiusura di entrambi i file
    fclose(src);
    fclose(dst);
    return 1;
}
