#include "errors.h"
#include "stdio.h"
#include "stdlib.h"

void exitProgram()
{
    exit(0);
}

void errorCouldNotOpenFile(char *filename)
{
    fprintf(stderr, "critical error:could not open file named :%s\n", filename);
    fprintf(stderr, "the program is shutting down...\n");
    exitProgram();
}
void errorCouldNotAllocateMemory()
{
    fprintf(stderr, "critical error:could not allocate new memory\n");
    fprintf(stderr, "the program is shutting down...\n");
    exitProgram();
}
void errorCouldNotSetEntry(int line, char *fileName, char *Extern)
{
    fprintf(stderr, "error:%s,%d: %s is an extern label,cannot be set as entry\n", fileName, line, Extern);
}

void errorDuplicateMacro(int line, char *mcro, char *fileName)
{
    fprintf(stderr, "error:%s,%d:macro %s has already been declared\n", fileName, line, mcro);
}
void errorDuplicateSymbol(int line, char *fileName, char *symbol)
{
    fprintf(stderr, "error:%s,%d:symbol %s has already been declared\n", fileName, line, symbol);
}

void errorIlegalLabel(int line, char *fileName, char *label)
{
    fprintf(stderr, "error:%s,%d:ilegal label %s ,all labels must start with a letter and continue with numbers or letter\n", fileName, line, label);
}
void errorIlegalInteger(int line, char *fileName, char *number)
{
    fprintf(stderr, "error:%s,%d:ilegal integer %s ,all integer's must be in format +/-[digit][digit]...\n", fileName, line, number);
}
void errorIlegalCharacter(int line, char *fileName, char ch)
{
    fprintf(stderr, "error:%s,%d:%c character is ilegal,must be letter,digit,comma,[,],:,=,_,.,+,-,#,''\n", fileName, line, ch);
}

void errorIlegalWordCount(int line, char *fileName, char *type)
{
    fprintf(stderr, "error:%s,%d:inproper amount of operands,in line of type %s\n", fileName, line, type);
}
void errorIlegalCharPlace(int line, char *fileName, char *axis, char *place, char ilegal, char *mustBe)
{
    fprintf(stderr, "error:%s,%d:%s %s %c is ilegal,must be %s\n", fileName, line, place, axis, ilegal, mustBe);
}
void errorIlegalWordPlace(int line, char *fileName, char *axis, char *place, char *ilegal, char *mustBe)

{
    fprintf(stderr, "error:%s,%d:%s %s %s is ilegal,must be %s\n", fileName, line, place, axis, ilegal, mustBe);
}

void errorMissingWord(int line, char *fileName, char *word)
{
    fprintf(stderr, "error:%s,%d:'%s' is missing in this line\n", fileName, line, word);
}
void errorMissingDecleration(int line, char *fileName, char *label)
{
    fprintf(stderr, "error:%s,%d:'%s' has not been declared yet\n", fileName, line, label);
}
