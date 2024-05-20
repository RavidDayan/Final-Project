#ifndef PARSER_H
#define PARSER_H

#include <stdio.h>
#include <stdlib.h>
#include "dataStructs.h"
#include "opcode.h"
#include "util.h"

#define MAX_LINE_CHARS 82 /*80 characters, 1 room for \n and 1 room for \0*/

char *removeWhiteSpace(FILE *file);               /*remove and adds whitespace without affecting original legality of syntax for eaiser tokenizing*/
char *getLine(FILE *file);                        /*rettrives line from FIle up to max line length allowed*/
int isLegalSyntax(char *line, MemoryManager *MM); /*checks if file is using legal syntax rules*/
int isIlegalCharacter(char ch);                   /*check if character is legal [letter,number,+,-,[,],.,',',",...]*/
LinkedList *getTokens(char *line);                /*seperates line into indivdual words seperated by , or whitespace*/
int isTokenSpacer(char ch);                       /*check if ch is a character that can seperate tokens*/
int isSpecialChar(char ch);                       /*check if ch is a character that needs special attention while removing and adding whitespace*/
/*check if token is what the functions is looking for*/
int isSavedWord(char *token);
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