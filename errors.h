#ifndef ERRORS_H
#define ERRORS_H

#define SAVE_SYSTEM_WORD 0
#define TOO_LONG_LINE  1
#define DUPLICATE_MACRO 2
#define DUPLICARE_SYMBOL 3
#define NOT_SYMBOL_OR_MDEFINE 4
#define NO_ILLEGAL_OPCODE 5
#define ILLEGAL_CHARACTER 6


void manageError(int line ,char *errorWord,int errorType);


#endif