#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "dataStructs.h"
#include "parser.h"
#include "util.h"
#include "errors.h"

void preProccess(MemoryManager *MM)
{
    /*variables*/
    int mcroFlag = FALSE; /*mcroflag:indicates if current characters belong to maco*/
    char *lineBuffer, *token;
    FILE *asFile, *organizedAsFile, *amFile; /*oragnizedFile:temporaryfile to hold the edited whitespace version of .as file*/
    Mcro *currentMcro;                       /*current*/
    asFile = openFile(getFT(MM->as), "r");
    if (asFile == NULL)
    {
        errorCouldNotOpenFile(getFT(MM->as)->name);
    }
    organizedAsFile = fopen(removeWhiteSpace(asFile), "r");
    CloseFile(getFT(MM->as));
    if (organizedAsFile == NULL)
    {
        errorCouldNotOpenFile("removeWhiteSpace.as");
    }
    else
    {
        amFile = openFile(getFT(MM->am), "w");
        if (amFile == NULL)
        {
            errorCouldNotOpenFile(getFT(MM->am)->name);
        }
        MM->currentLine = 0;

        lineBuffer = getLine(organizedAsFile);
        while (lineBuffer != NULL) /*find and spread macros in .am file*/
        {
            (MM->currentLine)++;
            if (strcmp(lineBuffer, "endmcr\n") == 0) /*signal end of macro and add macro to macro list*/
            {
                mcroFlag = FALSE;
                AddMcro(MM, newNode(currentMcro));
                fputc('\n', amFile);
            }
            else
            {
                if (mcroFlag == TRUE) /*allocate new memory for a new line and add it to  the current macro body*/
                {
                    if (currentMcro->data == NULL)
                    {
                        currentMcro->data = (char *)malloc(sizeof(char) * (strlen(lineBuffer) + 1));
                        if (currentMcro->data == NULL)
                        {
                            errorCouldNotAllocateMemory();
                        }
                        strcpy(currentMcro->data, lineBuffer);
                    }
                    else
                    {
                        currentMcro->data = (char *)realloc(currentMcro->data, sizeof(char) * (strlen(lineBuffer) + 1));
                        strcat(currentMcro->data, lineBuffer);
                    }
                    fputc('\n', amFile); /*replace the current line with \n in .am file*/
                }
                else
                {
                    if (isMacro(lineBuffer)) /*check for macro decleration*/
                    {
                        token = strtok(lineBuffer, " ");
                        token = strtok(NULL, " ");
                        if (mcroExists(token, MM) == NULL) /*check for duplicate macros*/
                        {
                            currentMcro = newMcro(token);
                            mcroFlag = TRUE;
                            fputc('\n', amFile);
                        }
                        else
                        {
                            errorDuplicateMacro(MM->currentLine, token, getFT(MM->as)->name);
                        }
                    }
                    else
                    {
                        currentMcro = mcroExists(lineBuffer, MM); /*insert relevant macro if theres a macro, otherise insert the line as is*/
                        if (currentMcro != NULL)
                        {
                            fputs(currentMcro->data, amFile);
                        }
                        else
                        {
                            fputs(lineBuffer, amFile);
                        }
                    }
                }
            }
            free(lineBuffer);
            lineBuffer = getLine(organizedAsFile);
        }
        CloseFile(MM->am->data);
        /*removeWhiteSpace.as is a temporary file as a fixed whitespace of .as,irelevant */
        fclose(organizedAsFile);
        remove("removeWhiteSpace.as");
    }
}
