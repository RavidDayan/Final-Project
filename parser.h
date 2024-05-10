#ifndef PARSER_H
#define PARSER_H

#include <stdio.h>
#include <stdlib.h>
#include "dataStructs.h"
#include "linkedList.h"
#include "node.h"

#define MAX_LINE_CHARS 82

char *removeWhiteSpace(FILE *file);
char *getLine(FILE *file);
LinkedList *getTokens(char *line);
int isSpecialChar(char ch);
void freeTokens(Node *token);
int isMdefine(char *token);
int isData(char *token);
int isString(char *token);
int isExtern(char *token);
int isEntry(char *token);
int isSymbol(char *token);

#endif