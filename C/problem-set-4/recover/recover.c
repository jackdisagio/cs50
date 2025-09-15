#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#pragma pack(push, 1)
typedef struct //total: 4-byte
{
    uint8_t a;
    uint8_t b;
    uint8_t c;
    uint8_t d;
}four;
#pragma pack(pop)

typedef uint8_t x; //1-byte

int number_TOT_block(FILE *input);
int *image_block(int TOT_block, FILE *input, int *count_image);
void write_image(int count_image, int *address, FILE *input, int TOT_block);

int main(int argc, char *argv[])
{
    if(argc != 2)
    {
        printf("use: %s [file_name]\n", argv[0]);
        return 0;
    }

    FILE *input = fopen(argv[1], "rb");
    if(input == NULL)
    {
        printf("file [%s] not found\n", argv[1]);
        return 0;
    }

    int TOT_block = number_TOT_block(input);
    int count_image = 0;
    int *address = image_block(TOT_block, input, &count_image);
    printf("numero di blocchi utili: %i\n", count_image); //done

    write_image(count_image, address, input, TOT_block);

    free(address);
    fclose(input);
}

void write_image(int count_image, int *address, FILE *input, int TOT_block)
{
    char filename[9];

    for(int i = 0; i < count_image; i++)
    {
        int difference = 0;
        fseek(input, (address[i]), SEEK_SET);

        if(i < count_image - 1) //done
        {
            difference = (address[i + 1] - address[i]);
        }
        else
        {
            difference = ((TOT_block * 512) - address[i]);
        }

        x *temp = malloc(difference * sizeof(x));

        fread(temp, sizeof(x), difference, input);
        sprintf(filename, "%03i.jpeg", i);

        FILE *temp_img = fopen(filename, "wb");
        if(temp_img == NULL)
        {
            printf("file di destinazione non valido\n");
            return;
        }

        fwrite(temp, sizeof(x), difference, temp_img);

        fclose(temp_img);
        free(temp);
    }
}

int *image_block(int TOT_block, FILE *input, int *count_image)
{
    x buffer[512];
    int block[512];

    for(int i = 0; i < TOT_block; i++)
    {
        fread(buffer, sizeof(x), 512, input);
        if(buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff)
        {
            block[*count_image] = i * 512;
            (*count_image)++;
        }
    }
    int *address = malloc((*count_image) * sizeof(int));
    for(int i = 0; i < *count_image; i++)
    {
        address[i] = block[i];
    }
    return address;
}

int number_TOT_block(FILE *input)
{
    int block = 0;
    x *temp = malloc(512);

    while(fread(&*temp, sizeof(x), 512, input) != EOF)
    {
        block++;
    }
    fseek(input, 0, SEEK_SET);
    free(temp);
    return block;
}
