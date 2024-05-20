#ifndef BINARY_H
#define BINARY_H

/*sets  from the 0 bit of a 14 bit memory,used for A,R,E*/
int setARE(int memory, int ARE);
/*sets from the 2 bit of a 14 bit memory,used for des addressing*/
int setDes(int memory, int Des);
/*sets from the 4 bit of a 14 bit memory,used for src addressing*/
int setSrc(int memory, int Src);
/*sets from the 5 bit of a 14 bit memory,used for entering register value*/
int setRegSrc(int memory, int reg);
/*sets from the 6 bit of a 14 bit memory,used for opcodes*/
int setCode(int memory, int Code);
/*sets from the 2 bit of a 14 bit memory,used for letters and numbers*/
int setValue(int memory, int Code);
/*prints the binary value of a number,used for testing*/
void printBinary(int num);
/*prints the quantinary hashed value of a number,used for testing*/
void binToQuantPrint(int binary, FILE *file);

#endif