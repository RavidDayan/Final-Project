#include <stdio.h>
#include "../headers/parser.h"
#include "../headers/util.h"
#include "../headers/opcode.h"
#include "../headers/dataStructs.h"
#include <string.h>
#include "../headers/errors.h"
#include "../headers/MemoryCollector.h"
void firstPass(MemoryManager *MM)
{
    FILE *amFile;
    LinkedList *tokenizedLine; /*tuens the string line into seprate tokens according to gettoken function*/
    Node *token;
    char *lineBuffer; /*holds line from .am file*/
    amFile = openFile(getFT(MM->am), "r");
    if (amFile == NULL)
    {
        errorCouldNotOpenFile(getFT(MM->am)->name);
    }
    MM->currentLine = 0;
    lineBuffer = getLine(amFile);
    while (lineBuffer != NULL) /*2*/
    {
        MM->currentLine++;
        if (strcmp(lineBuffer, "\n") != 0 && lineBuffer[0] != ';') /*check for empty line or comment line*/
        {
            if (isLegalSyntax(lineBuffer, MM) == TRUE) /*check for syntax errors*/
            {
                tokenizedLine = getTokens(lineBuffer);
                token = tokenizedLine->head;
                if (tokenizedLine != NULL)
                {
                    if (isMdefine(getStr(token)) == TRUE) /*if line starts with .mdefine inserts it to symbol table*/
                    {
                        insertMdefine(tokenizedLine, MM);
                    }
                    else
                    {
                        if (isSymbol(getStr(token)) == TRUE) /*check if line has a label decleration at the start*/
                        /*5*/
                        {
                            token = getNext(token);
                            if (token != NULL)
                            {
                                if (isData(getStr(token)) == TRUE) /*check if line is a data line*/
                                {
                                    insertData(tokenizedLine, MM);
                                }
                                else
                                {
                                    if (isString(getStr(token)) == TRUE) /*check if line is a string line*/
                                    {
                                        insertString(tokenizedLine, MM);
                                    }
                                    else
                                    {
                                        if (isOpCode(getStr(token)) != UNDEFINED) /*check if line is a operation line*/
                                        {
                                            insertCode(tokenizedLine, MM);
                                        }
                                        else /*no kind of line the starts with symbol has been found so this line is ilegal*/
                                        {
                                            errorMissingWord(MM->currentLine, getFT(MM->as)->name, "operation");
                                            MM->errorFlag = TRUE;
                                        }
                                    }
                                }
                            }
                            else /*if after label decleration there are no other operands this line is ilegal*/
                            {
                                errorMissingWord(MM->currentLine, getFT(MM->as)->name, "operation");
                                MM->errorFlag = TRUE;
                            }
                        }
                        else /*if there is no label line must be extern entry or operation, if its none ilegal line*/
                        {
                            if (isExtern(getStr(token)) == TRUE)
                            {
                                insertExtern(tokenizedLine, MM);
                            }
                            else
                            {
                                if (isEntry(getStr(token)) == FALSE)
                                {
                                    if (isOpCode(getStr(token)) >= 0)
                                    {
                                        insertCode(tokenizedLine, MM);
                                    }
                                    else
                                    {
                                        errorMissingWord(MM->currentLine, getFT(MM->as)->name, "legal operation");
                                        MM->errorFlag = TRUE;
                                    }
                                }
                            }
                        }
                    }
                }
            }
            else /*if syntax check is false, there is a error in .am file*/
            {
                MM->errorFlag = TRUE;
            }
        }
        lineBuffer = getLine(amFile);
    }
    /*if there is a error there is no point in moving on,if no errors, advance the address of all data lines by ic+100*/
    if (MM->errorFlag == TRUE)
    {
        return;
    }
    else
    {
        advanceData(MM); /*17*/
    }
}