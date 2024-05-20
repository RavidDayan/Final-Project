#ifndef OPCODE_H
#define OPCODE_H
/*opcode struct holds the name of the code,how many operands is needed,what typpe addressing is allowd for src and des*/
typedef struct opCode
{
    char code[4];
    int operands;
    int src[4];
    int des[4];

} opCode;
extern opCode codes[16];

int isOpCode(char *str);                  /*check if string is opcode from the list of codes,returns the opcode number*/
int enoughOperands(int size, int opCode); /*checks if the amount of operands in line matches the amount needed,returns true/false*/
int legalDesOp(int op, int opCode);       /*check if des addressing is legal in code,returns true/false*/
int legalSrcOp(int op, int opCode);       /*check if src addressing is legal in code,returns true/false*/
int getAddressingCode(char *token);       /*gets the addressing of a string [0,1,2,3] */
#endif
