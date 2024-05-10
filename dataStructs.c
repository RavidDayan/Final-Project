#include "dataStructs.h"
#include "stdlib.h"
#include "string.h"
#include "stdio.h"

Mcro *newMcro(char *name)
{
    Mcro *newMcro = (Mcro *)malloc(sizeof(Mcro));
    if (newMcro == NULL)
    {
        return NULL;
    }
    newMcro->name = (char *)malloc(strlen(name) + 1);
    if (newMcro->name == NULL)
    {
        free(newMcro);
        return NULL;
    }
    strcpy(newMcro->name, name);
    newMcro->data = NULL;
    return newMcro;
}