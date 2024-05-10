#include <stdio.h>
#include "parser.h"
#include "util.h"
#include "opcode.h"
#include "masking.h"
void firstPass(char *filename)
{
    int ic = 0, dc = 0, symbolFLag = FALSE, errorFlag = FALSE, L = 0;
    FILE *amFile = fopen(filename, "r");
    char *lineBuffer = getLine(amFile);
    LinkedList *tokenizedLine;
    Node *token;
    Memory memory[MEMORY_SIZE];
    while (lineBuffer != NULL) /*2*/
    {
        tokenizedLine = getTokens(lineBuffer);
        if (tokenizedLine != NULL)
        {
            if (isMdefine(lineBuffer) == TRUE) /*3*/
            {
                insertSymbol(lineBuffer, MDEFINE, dc); /*4*/
            }
            else
            {
                if (isSymbol(lineBuffer) == TRUE) /*5*/
                {
                    symbolFLag = TRUE;                                              /*6*/
                    if (isData(lineBuffer) == TRUE || isString(lineBuffer) == TRUE) /*7*/
                    {
                        if (isData(lineBuffer) == TRUE) /*8*/
                        {
                            insertSymbol(lineBuffer, DATA, dc);
                        }
                        else
                        {
                            insertSymbol(lineBuffer, STRING, dc);
                        }
                    }
                    else
                    {
                        if (isExtern(lineBuffer) == TRUE || isEntry(lineBuffer) == TRUE) /*10*/
                        {
                            if (isExtern(lineBuffer) == TRUE)
                            {
                                insertSymbol(lineBuffer, EXTERN, NULL);
                            }
                            else
                            {
                                insertSymbol(lineBuffer, ENTRY, NULL);
                            }
                        }
                        else
                        {
                            insertSymbol(lineBuffer, CODE, ic + 100); /*12*/
                            if (isOpCode(lineBuffer) >= 0)
                            {                            /*13*/
                                anaylzeLine(lineBuffer); /*14*/
                                ic = ic + L;             /*15*/
                            }
                            else
                            {
                                /*print error no opcode*/
                            }
                        }
                    }
                }
            }
            free(lineBuffer);
        }
    }
    if (errorFlag == TRUE)
    {
    }
    else
    {
        advanceData(ic + 100);
        /*second pass*/
        ic = 0; /*1*/
        rewind(amFile);
        while (lineBuffer != NULL) /*2*/
        {
            if (isSymbol(lineBuffer) == FALSE) /*3*/
            {
                if (isData(lineBuffer) != TRUE && isString(lineBuffer) != TRUE && isExtern(lineBuffer) != TRUE) /*4*/
                {
                    if (isEntry(lineBuffer) == TRUE) /*5*/
                    {
                        /*mark symbols with entry*/ /*6*/
                    }
                    else
                    {
                        /*7*/
                        ic = ic + L; /*8*/
                    }
                }
            }
            free(lineBuffer);
        }
        if (errorFlag == TRUE)
        {
            /*handle error*/
        }
        else
        {
            buildFiles();
        }
    }
}