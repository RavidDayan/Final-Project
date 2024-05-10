#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "preProccess.h"
#include "linkedList.h"
/*#include "dataStructs.h"*/

void assemble(char *fileName, LinkedList *mcros);
int main(int argc, char *argv[])
{
    /*memory stack[4096];*/
    LinkedList *mcros;
    int i;
    if (argc == 1)
    {
        fprintf(stderr, "No file name has been enterd");
        exit(EXIT_FAILURE);
    }

    for (i = 1; i < argc; i++)
    {
        mcros = newLinkedList();
        assemble(argv[i], mcros);
    }

    return 0;
}
void assemble(char *fileName, LinkedList *mcros)
{
    preProccess(fileName, mcros);
}