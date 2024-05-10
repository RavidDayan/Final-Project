#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "preProccess.h"
#include "dataStructs.h"
#include "parser.h"
#include "linkedList.h"
#include "util.h"

void preProccess(char *fileName, LinkedList *mcros)
{
    int mcroFlag = FALSE;
    char *lineBuffer, *token;
    FILE *inputFile, *organizedInputFile, *preProccessedFile;
    Mcro *currentMcro;
    inputFile = fopen(fileName, "r");
    if (inputFile == NULL)
    {
        perror("Error opening input file");
    }
    organizedInputFile = fopen(removeWhiteSpace(inputFile), "r");
    fclose(inputFile);
    if (organizedInputFile == NULL)
    {
        perror("Error opening organizedInputFile file");
    }
    else
    {
        preProccessedFile = fopen(changeAsToAm(fileName), "w");
        if (preProccessedFile == NULL)
        {
            perror("Error creating output file");
            fclose(inputFile);
        }
        lineBuffer = getLine(organizedInputFile);
        while (lineBuffer != NULL)
        {
            if (strcmp(lineBuffer, "endmcr\n") == 0)
            {
                mcroFlag = FALSE;
                append(mcros,newNode(currentMcro));
                fputc('\n', preProccessedFile);
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
                    fputc('\n', preProccessedFile);
                }
                else
                {
                    if (isMacro(lineBuffer))
                    {
                        token = strtok(lineBuffer, " ");
                        token = strtok(NULL, " ");
                        if (mcroExists(token, mcros) == NULL)
                        {
                            currentMcro = newMcro(token);
                            mcroFlag = TRUE;
                            fputc('\n', preProccessedFile);
                        }
                        else
                        {
                            /*ERROR:duplicate macros*/
                        }
                    }
                    else
                    {
                        currentMcro = mcroExists(lineBuffer, mcros);
                        if (currentMcro != NULL)
                        {
                            fputs(currentMcro->data, preProccessedFile);
                        }
                        else
                        {
                            fputs(lineBuffer, preProccessedFile);
                        }
                    }
                }
            }
            free(lineBuffer);
            lineBuffer = getLine(organizedInputFile);
        }
        fclose(preProccessedFile);
        fclose(organizedInputFile);
        remove("removeWhiteSpace.as");
    }
}
char *changeAsToAm(char *as)
{
    char *am;
    am = (char *)malloc((strlen(as) + 1) * sizeof(char));
    strcpy(am, as);
    am[strlen(as) - 1] = 'm';
    return am;
}
int isMacro(char *line)
{
    if (line[0] == 'm' && line[1] == 'c' && line[2] == 'r' && line[3] == ' ')
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

Mcro *mcroExists(char *newMcro, LinkedList *mcros)
{
    char *mcroName;
    Mcro *mcro;
    Node *mcroNode = mcros->head;
    while (mcroNode != NULL)
    {
        mcro = (Mcro *)mcroNode->data;
        mcroName = mcro->name;
        if (strcmp(newMcro, mcroName) == 0)
        {
            {
                return mcro;
            }
        }
        mcroNode = mcroNode->next;
    }
    return NULL;
}