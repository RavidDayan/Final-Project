#include <stdio.h>
int setARE(int memory, int ARE)
{
    memory = memory | ARE;
    return memory;
}
int setDes(int memory, int Des)
{
    memory = memory | (Des << 2);
    return memory;
}
int setSrc(int memory, int Src)
{
    memory = memory | (Src << 4);
    return memory;
}
int setRegSrc(int memory, int reg)
{
    memory = memory | (reg << 5);
    return memory;
}
int setCode(int memory, int Code)
{
    memory = memory | (Code << 6);
    return memory;
}
int setValue(int memory, int data)
{
    memory = memory | (data << 2);
    return memory;
}
void printBinary(int num)
{
    int i;
    int bit;
    for (i = 13; i >= 0; i--)
    {
        bit = num;
        bit = (num >> i) & 1;
        printf("%d", bit);
    }
    printf("\n");
}
void binToQuantPrint(int binary, FILE *file)
{
    char *quant[7];
    int i, j = 0;
    int quad;
    for (i = 12; i >= 0; i = i - 2)
    {
        quad = (binary >> i) & 3;
        switch (quad)
        {
        case 0:
            quant[j] = '*';
            break;
        case 1:
            quant[j] = '#';
            break;
        case 2:
            quant[j] = '%';
            break;
        case 3:
            quant[j] = '!';
            break;
        }
        fprintf(file, "%c", quant[j]);
        j++;
    }
    fprintf(file, "\n");
}