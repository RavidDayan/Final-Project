#ifndef ERRORS_H
#define ERRORS_H

void exitProgram();

void errorCouldNotOpenFile(char *filename);
void errorCouldNotAllocateMemory();
void errorCouldNotSetEntry(int line, char *fileName, char *Extern);

void errorDuplicateMacro(int line, char *mcro, char *fileName);
void errorDuplicateSymbol(int line, char *fileName, char *symbol);

void errorIlegalLabel(int line, char *fileName, char *label);
void errorIlegalInteger(int line, char *fileName, char *number);
void errorIlegalCharacter(int line, char *fileName, char ch);
void errorIlegalWordCount(int line, char *fileName, char *type);
void errorIlegalCharPlace(int line, char *fileName, char *axis,char *place ,char ilegal,char *mustBe);
void errorIlegalWordPlace(int line, char *fileName, char *axis,char *place ,char *ilegal,char *mustBe);

void errorMissingWord(int line, char *fileName, char *word);
void errorMissingDecleration(int line, char *fileName, char *label);


#endif