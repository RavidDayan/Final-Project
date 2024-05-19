#ifndef ERRORS_H
#define ERRORS_H
#define NO_TOKEN 1
#define NO_LINE -1

#define SAVED_SYSTEM_WORD 2
#define LINE_TOO_LONG 3

#define DUPLICATE_MACRO 4
#define DUPLICATE_SYMBOL 5

#define ILLEGAL_LABEL 1
#define ILLEGAL_OPCODE 1
#define ILLEGAL_CHARACTER 1
#define ILLEGAL_CODE_LINE 1
#define ILLEGAL_CHARACTER_BEFORE 1
#define ILLEGAL_CHARACTER_AFTER 1
#define ILLEGAL_CONSECUTIVE 1

#define COULD_NOT_ENTRY_EXTERN 1
#define COULD_NOT_ALLOCATE_MEMORY 1
#define COULD_NOT_MATCH_WORDS_COUNT 1
#define COULD_NOT_DECALRE_TWICE 1

#define NOT_EXISTS_SYMBOL 1

#define NO_EQUAL_SIGN 1
#define NO_STRING_START_END 1
#define NO_MISSING_BRACKETS 1

void exitProgram();

void errorCouldNotOpenFile(char *filename);
void errorCouldNotAllocateMemory();
void errorCouldNotSetEntry(int line, char *fileName, char *Extern);

void errorDuplicateMacro(int line, char *mcro, char *fileName);
void errorDuplicateSymbol(int line, char *fileName, char *symbol);

void errorIlegalLabel(int line, char *fileName, char *label);
void errorIlegalInteger(int line, char *fileName, char *number);
void errorIlegalWordCount(int line, char *fileName, char *type);

void errorMissingWord(int line, char *fileName, char *word);
void errorMissingDecleration(int line, char *fileName, char *label);


#endif