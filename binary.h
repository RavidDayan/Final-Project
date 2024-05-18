#ifndef BINARY_H
#define BINARY_H

int setARE(int memory,int ARE);
int setDes(int memory,int Des);
int setSrc(int memory,int Src);
int setRegSrc(int memory, int reg);
int setCode(int memory,int Code);
int setValue(int memory,int Code);
void printBinary(int num);
void binToQuantPrint(int binary, FILE *file);
#endif