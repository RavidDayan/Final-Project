typedef struct opCode
{
    char code[4];
    int operands;
    int src[4];
    int des[4];

} opCode;
extern opCode codes[16];

int isOpCode(char *str);
int enoughOperands(int size,int opCode);
int legalDesOp(int op,int opCode);
int legalSrcOp(int op,int opCode);
int getAddressingCode(char *token);

