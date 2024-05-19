#include <stdlib.h>
#include "stdio.h"
#include "secondPass.h"
#include "util.h"
#include "dataStructs.h"
#include "parser.h"
#include "binary.h"
#include "errors.h"
void secondPass(MemoryManager *MM)
{
    FILE *amFile;
    MemoryLine *ML;
    Node *token, *code;
    LinkedList *tokenizedLine;
    Symbol *symbol;
    char *lineBuffer;
    amFile = openFile(getFT(MM->am), "r");
    if (amFile == NULL)
    {
        errorCouldNotOpenFile(getFT(MM->am)->name);
    }
    lineBuffer = getLine(amFile);
    while (lineBuffer != NULL) /*2*/
    {
        if (lineBuffer[0] != '\n' && lineBuffer[0] != ';')
        {
            tokenizedLine = getTokens(lineBuffer);
            token = tokenizedLine->head;
            if (isEntry(getStr(token)) == TRUE)
            {
                insertEntry(tokenizedLine, MM);
            }
        }
        free(lineBuffer);
        /*free tokenized line*/
        lineBuffer = getLine(amFile);
    }
    code = MM->code;
    while (code != NULL)
    {
        ML = getML(code);
        if (ML->BMC == UNDEFINED)
        {
            symbol = symbolExists(getStr(ML->SC), MM);
            if (symbol != NULL)
            {
                ML->BMC = setValue(0, symbol->value);
                if (symbol->property != EXTERN)
                {
                    ML->BMC = setARE(ML->BMC, ENTRY);
                    ML->type = ENTRY;
                }
            }
            else
            {
                errorMissingDecleration(MM->currentLine, getFT(MM->as)->name, getStr(ML->SC));
                MM->errorFlag = TRUE;
            }
        }
        code = getNext(code);
    }

    if (MM->errorFlag == TRUE)
    {

        printf("error");
        /*handle error*/
    }
    else
    {
        printf("\n");
        printAll(MM);
    }
}