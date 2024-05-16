#ifndef PARSER_H
#define PARSER_H

#include <stdio.h>
#include <stdlib.h>
#include "dataStructs.h"

#define MAX_LINE_CHARS 82

char *removeWhiteSpace(FILE *file);
char *getLine(FILE *file);
int isLegalSyntax(char *line);
int isIlegalCharacter(char ch);
LinkedList *getTokens(char *line);
int isSpecialChar(char ch);
int isMdefine(char *token);
int isData(char *token);
int isInteger(char *token);
int isString(char *token);
int isExtern(char *token);
int isEntry(char *token);
int isSymbol(char *token);
int isMacro(char *line);
int isArray(char *token);
int isRegister(char *token);

#endif