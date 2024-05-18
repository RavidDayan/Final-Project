#include <stdio.h>
#include "parser.h"
#include "util.h"
#include "opcode.h"
#include "dataStructs.h"
#include <string.h>
void firstPass(MemoryManager *MM)
{
    FILE *amFile;
    LinkedList *tokenizedLine;
    
    Node *token;
    char *lineBuffer;
    amFile = openFile(getFT(MM->am), "r");
    if (amFile == NULL)
    {
        /*error*/
    }
    lineBuffer = getLine(amFile);
    while (lineBuffer != NULL) /*2*/
    {
        printf("%s\n",lineBuffer);
        if (strcmp(lineBuffer, "\n")!=0 && lineBuffer[0]!=';')
        {
            if (isLegalSyntax(lineBuffer) == TRUE)
            {
                tokenizedLine = getTokens(lineBuffer);
                token = tokenizedLine->head;
                if (tokenizedLine != NULL)
                {
                    if (isMdefine(getStr(token)) == TRUE) /*3*/
                    {
                        insertMdefine(tokenizedLine, MM); /*4*/
                    }
                    else
                    {
                        if (isSymbol(getStr(token)) == TRUE) /*check if instruction, data or string*/
                        /*5*/
                        {
                            token = getNext(token);
                            if (isData(getStr(token)) == TRUE) /*8*/
                            {
                                insertData(tokenizedLine, MM);
                            }
                            if (isString(getStr(token)) == TRUE) /*8*/
                            {
                                insertString(tokenizedLine, MM);
                            }
                            if (isOpCode(getStr(token)) != UNDEFINED)
                            {
                                insertCode(tokenizedLine, MM);
                            }
                        }
                        else /*extern,instruction line,undefined*/
                        {
                            if (isExtern(getStr(token)) == TRUE)
                            {
                                insertExtern(tokenizedLine, MM);
                            }
                            if (isEntry(getStr(token)) == FALSE)
                            {
                                if (isOpCode(getStr(token)) >= 0)
                                { /*13*/
                                    insertCode(tokenizedLine, MM);
                                }
                                else
                                {
                                    /*error: no opcode*/
                                }
                            }
                        }
                    }
                }
            }
            else
            {
                MM->errorFlag = TRUE;
            }
            free(lineBuffer);
        }
        lineBuffer = getLine(amFile);
        if (MM->errorFlag == TRUE) /*16*/
        {
            /*error*/
        }
    }
    if (MM->errorFlag == TRUE) /*16*/
    {

        /*error*/
    }
    else
    {
        advanceData(MM); /*17*/
        printAll(MM);
    }
}