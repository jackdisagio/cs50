// Modifies the volume of an audio file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44; //(352-bit)

typedef int16_t x; //2 byte
typedef int8_t y; //1 byte

int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Open files and determine scaling factor
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    float factor = atof(argv[3]); //trasforma in valore

    // TODO: Copy header from input file to output file
    for(int i = 0; i < HEADER_SIZE; i++)
    {
        y temp = 0;
        fread(&temp, sizeof(temp), 1, input);
        fwrite(&temp, sizeof(temp), 1, output);
    }

    // TODO: Read samples from input file and write updated data to output file
    fseek(input, 44, SEEK_SET);
    fseek(output, 44, SEEK_SET);

    int count = 0;
    x temp; //temp a 2-byte
    while(fread(&temp, sizeof(temp), 1, input) != EOF) //trascrizzione del byte in temp (2-byte)
    {
        temp = temp * factor;
        fwrite(&temp, sizeof(temp), 1, output);
        count++;
    }

    printf("byte: %i\n", count);
    fclose(input);
    fclose(output);
}
