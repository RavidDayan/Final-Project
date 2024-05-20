#include <stdlib.h>
#include "stdio.h"
#include "../headers/secondPass.h"
#include "../headers/util.h"
#include "../headers/dataStructs.h"
#include "../headers/parser.h"
#include "../headers/binary.h"
#include "../headers/errors.h"
#include "../headers/MemoryCollector.h"
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
    MM->currentLine = 0;
    lineBuffer = getLine(amFile);
    while (lineBuffer != NULL) /*look for .entry lines*/
    {
        MM->currentLine++;
        if (lineBuffer[0] != '\n' && lineBuffer[0] != ';') /*skip empty or comment lines*/
        {
            tokenizedLine = getTokens(lineBuffer);
            token = tokenizedLine->head;
            if (isEntry(getStr(token)) == TRUE) /*check if entry and insert symbol as entry*/
            {
                insertEntry(tokenizedLine, MM);
            }
        }
        lineBuffer = getLine(amFile);
    }
    code = MM->code;
    MM->currentLine = 0;
    while (code != NULL) /*look for code lines that are undefined from first pass*/
    {
        MM->currentLine++;
        ML = getML(code);
        if (ML->BMC == UNDEFINED) /*skip defined lines*/
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
                if (symbol->property == EXTERN)
                {
                    ML->BMC = setARE(ML->BMC, EXTERN);
                    ML->type = EXTERN;
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
}