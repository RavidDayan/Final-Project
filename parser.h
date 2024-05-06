#ifndef PARSER_H
#define PARSER_H

#include <stdio.h>
#include <stdlib.h>
#include "dataStructs.h"

#define MAX_LINE_CHARS 82;

void removeWhiteSpace(FILE *file);
char *getLine(FILE *file);
tokenNode *getToken(char *line);
/*int isStructureLegal(char *line);
int isDefined(char name);*/
#endif