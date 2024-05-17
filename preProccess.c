#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "dataStructs.h"
#include "parser.h"
#include "util.h"

void preProccess(MemoryManager *MM)
{
    int mcroFlag = FALSE;
    char *lineBuffer, *token;
    FILE *asFile, *organizedAsFile, *amFile;
    Mcro *currentMcro;
    asFile = openFile(getFT(MM->as), "r");
    if (asFile == NULL)
    {
        /*error*/
    }
    organizedAsFile = fopen(removeWhiteSpace(asFile), "r");
    CloseFile(MM->as->data);
    if (organizedAsFile == NULL)
    {
        /*error*/
    }
    else
    {
        amFile = openFile(MM->am->data, "w");
        if (amFile == NULL)
        {
            /*error*/
        }
        lineBuffer = getLine(organizedAsFile);
        while (lineBuffer != NULL)
        {
            if (strcmp(lineBuffer, "endmcr\n") == 0)
            {
                mcroFlag = FALSE;
                AddMcro(MM, newNode(currentMcro));
                fputc('\n', amFile);
            }
            else
            {
                if (mcroFlag == TRUE)
                {
                    if (currentMcro->data == NULL)
                    {
                        currentMcro->data = (char *)malloc(sizeof(char) * (strlen(lineBuffer) + 1));
                        strcpy(currentMcro->data, lineBuffer);
                    }
                    else
                    {
                        currentMcro->data = (char *)realloc(currentMcro->data, sizeof(char) * (strlen(lineBuffer) + 1));
                        strcat(currentMcro->data, lineBuffer);
                    }
                    fputc('\n', amFile);
                }
                else
                {
                    if (isMacro(lineBuffer))
                    {
                        token = strtok(lineBuffer, " ");
                        token = strtok(NULL, " ");
                        if (mcroExists(token, MM) == NULL)
                        {
                            currentMcro = newMcro(token);
                            mcroFlag = TRUE;
                            fputc('\n', amFile);
                        }
                        else
                        {
                            /*ERROR:duplicate macros*/
                        }
                    }
                    else
                    {
                        currentMcro = mcroExists(lineBuffer, MM);
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
        fclose(organizedAsFile);
        remove("removeWhiteSpace.as");
    }
}
