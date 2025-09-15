#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

#pragma pack(push, 1)
typedef struct//tot: 3-byte
{
    uint8_t B;
    uint8_t G;
    uint8_t R;
}BGR;
#pragma pack(pop)

typedef struct//tot: 12-byte (no padding)
{
    uint32_t B;
    uint32_t G;
    uint32_t R;
}bgr;

typedef int32_t x; //4-byte
typedef int8_t y; //1-byte
typedef uint8_t z; //1-byte (+)

int mirror(x Width, x Height, FILE *input, FILE *output,  BGR temp[]);
void W_H(x *Width, x *Height, FILE *input);
void jump_header(FILE *input, FILE *output);
void Reflect(FILE *input, FILE *output); //filter 1
void Grayscale(FILE *input, FILE *output); //filter 2
void average(x Width, x Height, FILE *input, FILE *output);
void Blur(FILE *input, FILE *output); // filter 3
void average_3x3(x Width, x Height, FILE *input, FILE *output);
void Edges(FILE *input, FILE *output); //filter 4
void copy(FILE *input, FILE *output); //filter 5
void weighted_sum(x Width, x Height, FILE *input, FILE *output);
void Gx_Gy(bool array[3][3], BGR *image, x Width, x Height, int i, int j, y Gx_tab[3][3], bgr *Gx, y Gy_tab[3][3], bgr *Gy);
void Gx_(y Gy_tab[3][3], bgr *Gx, BGR BGR_array[3][3]);
void Gy_(y Gy_tab[3][3], bgr *Gy, BGR BGR_array[3][3]);

int main(int argc, char *argv[])
{
    if(argc != 4)
    {
        printf("use: %s [flag] [input.bmp] [output.bmp]\n", argv[0]);
        return 0;
    }

    FILE *input = fopen(argv[2], "rb");
    if(input == NULL)
    {
        printf("file [%s] not found\n", argv[2]);
        return 0;
    }

    FILE *output = fopen(argv[3], "wb");
    if(output == NULL)
    {
        printf("file [%s] not found\n", argv[3]);
        return 0;
    }

    switch(argv[1][1])
    {
        case 'g':
        {
            Grayscale(input, output); //done
            break;
        }
        case 'r':
        {
            Reflect(input, output); //done
            break;
        }
        case 'b':
        {
            Blur(input, output); //done
            break;
        }
        case 'e':
        {
            Edges(input, output);
            break;
        }
        case 'c':
        {
            copy(input, output); //done
            break;
        }
        default:
        {
            printf("use [flag]: -g / -r / -b / -e / -c\n");
            break;
        }
    }

    fclose(input);
    fclose(output);
}

void weighted_sum(x Width, x Height, FILE *input, FILE *output)
{
    BGR *image = malloc((Height * Width) * sizeof(BGR));
    fread(image, sizeof(BGR), (Height * Width), input);
    BGR *image_edge = malloc((Height * Width) * sizeof(BGR));
    y Gx_tab[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    y Gy_tab[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};


    char c = get_char("do you want normal edge? [y/n] ");
    c = tolower(c);


    while(c != 'n' && c != 'y')
    {
        printf("type: [y] or [n]");
        c = get_char(" ");
    }


    bool array[3][3];

    for(int i = 0; i < Height; i++)
    {
        for(int j = 0; j < Width; j++)
        {
            for(int l=0; l<3; l++)
            {
                for(int n=0; n<3; n++)
                {
                    array[l][n] = (i + l - 1 >= 0 && i + l - 1 < Height &&
                    j + n - 1 >= 0 && j + n - 1 < Width);
                }
            }

            bgr Gx;
            bgr Gy;
            bgr G;
            double factor = (float)255 / 1448;

            Gx_Gy(array, image, Width, Height, i, j, Gx_tab, &Gx, Gy_tab, &Gy);

            double sum_B = (Gx.B * Gx.B) + (Gy.B * Gy.B);
            double sum_G = (Gx.G * Gx.G) + (Gy.G * Gy.G);
            double sum_R = (Gx.R * Gx.R) + (Gy.R * Gy.R);

            G.B = round((sqrt(sum_B)) * factor);
            G.G = round((sqrt(sum_G)) * factor);
            G.R = round((sqrt(sum_R)) * factor);

            if(G.B > 255) {G.B = 255;}
            if(G.G > 255) {G.G = 255;}
            if(G.R > 255) {G.R = 255;}

            if(c == 'n')
            {
                image_edge[(i * Width) + j].B = (uint8_t)G.B;
                image_edge[(i * Width) + j].G = (uint8_t)G.G;
                image_edge[(i * Width) + j].R = (uint8_t)G.R;
            }
            else
            {
                image_edge[(i * Width) + j].B = (uint8_t)(G.B + G.G + G.R) / 2;
                image_edge[(i * Width) + j].G = image_edge[(i * Width) + j].B;
                image_edge[(i * Width) + j].R = image_edge[(i * Width) + j].B;
            }
        }
    }
    fwrite(image_edge, sizeof(BGR), (Height * Width), output);
    free(image);
    free(image_edge);
}

void Gx_Gy(bool array[3][3], BGR *image, x Width, x Height, int i, int j, y Gx_tab[3][3], bgr *Gx, y Gy_tab[3][3], bgr *Gy)
{
    BGR BGR_array[3][3];

    for(int l = 0; l < 3; l++)
    {
        for(int n = 0; n < 3; n++)
        {
            if(array[l][n] == 0)
            {
                BGR_array[l][n].B = 0x00;
                BGR_array[l][n].G = 0x00;
                BGR_array[l][n].R = 0x00;
            }
            else
            {
                BGR_array[l][n] = image[(i + l - 1) * Width + (j + n - 1)];
            }
        }
    }

    Gx_(Gx_tab, Gx, BGR_array);
    Gy_(Gy_tab, Gy, BGR_array);
}

void Gy_(y Gy_tab[3][3], bgr *Gy, BGR BGR_array[3][3])
{
    bgr tot_Gy = {0, 0, 0};
    for(int l = 0; l < 3; l++)
    {
        for(int n = 0; n < 3; n++)
        {
            tot_Gy.B += (BGR_array[l][n].B * (Gy_tab[l][n]));
            tot_Gy.G += (BGR_array[l][n].G * (Gy_tab[l][n]));
            tot_Gy.R += (BGR_array[l][n].R * (Gy_tab[l][n]));
        }
    }
    memcpy(Gy, &tot_Gy, sizeof(bgr));
}

void Gx_(y Gx_tab[3][3], bgr *Gx, BGR BGR_array[3][3])
{
    bgr tot_Gx = {0, 0, 0};
    for(int l = 0; l < 3; l++)
    {
        for(int n = 0; n < 3; n++)
        {
            tot_Gx.B += (BGR_array[l][n].B * (Gx_tab[l][n]));
            tot_Gx.G += (BGR_array[l][n].G * (Gx_tab[l][n]));
            tot_Gx.R += (BGR_array[l][n].R * (Gx_tab[l][n]));
        }
    }
    memcpy(Gx, &tot_Gx, sizeof(bgr));
}

void Edges(FILE *input, FILE *output)
{
    x Width;
    x Height;
    W_H(&Width, &Height, input);
    jump_header(input, output);
    weighted_sum(Width, Height, input, output);
}

void copy(FILE *input, FILE *output)
{
    x Width;
    x Height;
    W_H(&Width, &Height, input);
    jump_header(input, output);

    BGR *image = malloc((Width * Height) * sizeof(BGR));
    fread(image, sizeof(BGR), (Width * Height), input);
    fwrite(image, sizeof(BGR), (Width * Height), output);
}

void average_3x3(x Width, x Height, FILE *input, FILE *output)
{
    BGR *image = malloc((Height * Width) * sizeof(BGR));
    fread(image, sizeof(BGR), (Height * Width), input); //done
    BGR *image_blur = malloc((Height * Width) * sizeof(BGR));

    bool array[3][3];
    array[1][1] = 1;
    BGR av;
    for(int i = 0; i < Height; i++)
    {
        for(int j = 0; j < Width; j++)
        {
            int count = 0;
            bgr average = {0, 0, 0};

            for(int l=0; l<3; l++)
            {
                for(int n=0; n<3; n++)
                {
                    array[l][n] = (i + l - 1 >= 0 && i + l - 1 < Height &&
                    j + n - 1 >= 0 && j + n - 1 < Width);
                }
            }

            for(int l = 0; l < 3; l++)
            {
                for(int n = 0; n < 3; n++)
                {
                    BGR sum = {0, 0, 0};
                    if(array[l][n] == 1)
                    {
                        average.B += image[(i + l) * Width + (j + n)].B;
                        average.G += image[(i + l) * Width + (j + n)].G;
                        average.R += image[(i + l) * Width + (j + n)].R;
                        count++;
                    }
                }
            }
            av.B = average.B / count;
            av.G = average.G / count;
            av.R = average.R / count;
            image_blur[((i) * Width) + j].B = av.B;
            image_blur[((i) * Width) + j].G = av.G;
            image_blur[((i) * Width) + j].R = av.R;
        }
    }
    fwrite(image_blur, sizeof(BGR), (Height * Width), output);
    free(image);
    free(image_blur);
}

void Blur(FILE *input, FILE *output)
{
    x Width;
    x Height;
    W_H(&Width, &Height, input);
    jump_header(input, output);
    average_3x3(Width, Height, input, output);
}

void Grayscale(FILE *input, FILE *output)
{
    x Width;
    x Height;
    W_H(&Width, &Height, input);
    jump_header(input, output);
    average(Width, Height, input, output);
}

void Reflect(FILE *input, FILE *output)
{
    x Width;
    x Height;
    W_H(&Width, &Height, input);
    BGR temp[Width];
    jump_header(input, output);
    mirror(Width, Height, input, output, temp);
}

void average(x Width, x Height, FILE *input, FILE *output)
{
    BGR temp;
    z average;
    for(int i = 0; i < Height; i++)
    {
        for(int j = 0; j < Width; j++)
        {
            fread(&temp, sizeof(temp), 1, input);
            average = (temp.B + temp.R + temp.G) / 3;
            BGR gray = {average, average, average};
            fwrite(&gray, sizeof(gray), 1, output);
        }
    }
}

void jump_header(FILE *input, FILE *output)
{
    y header;
    fseek(input, 0, SEEK_SET); //riparti da 0
    for(int i = 0; i < 54; i++)
    {
        fread(&header, sizeof(header), 1, input);
        fwrite(&header, sizeof(header), 1, output);
    }
}

void W_H(x *Width, x *Height, FILE *input)
{
    fseek(input, 18, SEEK_SET); // arrivare al 18^
    {
        fread(Width, sizeof(*Width), 1, input);
        fread(Height, sizeof(*Height), 1, input);
    }
    *Width = abs(*Width);
    *Height = abs(*Height);
    printf("Width: %d\nHeight: %d\n", *Width, *Height);
}

int mirror(x Width, x Height, FILE *input, FILE *output, BGR temp[])
{
    int count = 0;
    for(int i = 0; i < Height; i++)
    {
        for(int j = 0; j < Width; j++)
        {
            fread(&temp[j], sizeof(temp[j]), 1, input);
        }
        for(int j = 0; j < Width; j++)
        {
            fwrite(&temp[Width - j - 1], sizeof(temp[Width - j - 1]), 1, output);
            count++;
        }
    }
    return count;
}
