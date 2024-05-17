#include <string.h>
#include "opcode.h"
#include "util.h"
#include "dataStructs.h"
#include "parser.h"

opCode codes[16] = {
    {"mov", 2, {1, 1, 1, 1}, {0, 1, 1, 1}},
    {"cmp", 2, {1, 1, 1, 1}, {1, 1, 1, 1}},
    {"add", 2, {1, 1, 1, 1}, {0, 1, 1, 1}},
    {"sub", 2, {1, 1, 1, 1}, {0, 1, 1, 1}},
    {"not", 1, {0, 0, 0, 0}, {0, 1, 1, 1}},
    {"clr", 1, {0, 0, 0, 0}, {0, 1, 1, 1}},
    {"lea", 2, {0, 1, 1, 0}, {0, 1, 1, 1}},
    {"inc", 1, {0, 0, 0, 0}, {0, 1, 1, 1}},
    {"dec", 1, {0, 0, 0, 0}, {0, 1, 1, 1}},
    {"jmp", 1, {0, 0, 0, 0}, {0, 1, 0, 1}},
    {"bne", 1, {0, 0, 0, 0}, {0, 1, 0, 1}},
    {"red", 1, {0, 0, 0, 0}, {0, 1, 1, 1}},
    {"prn", 1, {0, 0, 0, 0}, {1, 1, 1, 1}},
    {"jsr", 1, {0, 0, 0, 0}, {0, 1, 0, 1}},
    {"rts", 0, {0, 0, 0, 0}, {0, 0, 0, 0}},
    {"hlt", 0, {0, 0, 0, 0}, {0, 0, 0, 0}}
    };

int isOpCode(char *opCode)
{
    int i = 0;
    for (i = 0; i < 16; i++)
    {
        if (strcmp(codes[i].code, opCode) == 0)
        {
            return i;
        }
    }
    return UNDEFINED;
}
int enoughOperands(int size, int opCode)
{
    if (codes[opCode].operands == size)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}
int legalDesOp(int des, int opCode)
{
    return codes[opCode].des[des];
}
int legalSrcOp(int src, int opCode)
{
    return codes[opCode].src[src];
}
int getAddressingCode(char *token)
{
    if (token[0] == '#')
    {
        return 0;
    }
    if (isArray(token) == TRUE)
    {
        return 2;
    }
    if (isRegister(token)!=UNDEFINED)
    {
        return 3;
    }
    return 1;
}