#ifndef PRE_PROCCESS_H
#define PRE_PROCCESS_H
#include "linkedList.h"
#include "dataStructs.h"


void preProccess(char *fileName, LinkedList *mcros);
char *changeAsToAm(char *as);
Mcro *mcroExists(char *newMcro, LinkedList *mcros);
int isMacro(char *line);
int isLabelNamedMacro();

#endif