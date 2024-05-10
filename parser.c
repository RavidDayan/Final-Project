#include "parser.h"
#include "dataStructs.h"
#include "node.h"
#include "linkedList.h"
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "util.h"

char *removeWhiteSpace(FILE *input)
{
    FILE *newFile;
    char buffer;
    char *organizedFile = "removeWhiteSpace.as";
    char lastInserted = ' ';
    int stringFlag = 0;
    int sqBracketsFlag = 0;
    buffer = fgetc(input);
    newFile = fopen(organizedFile, "w");
    while (buffer != EOF)
    {
        if (buffer == '"')
        {
            if (stringFlag == 1)
            {
                stringFlag = 0;
            }
            else
            {
                stringFlag = 1;
            }
        }
        if (buffer == '[')
        {
            sqBracketsFlag = 1;
        }
        if (buffer == ']')
        {
            sqBracketsFlag = 0;
        }
        /*check if char is a non \n white space not in a string*/
        if (isspace(buffer) && buffer != '\n' && stringFlag == 0)
        {
            /*if the last character is  a white space and its a string add to file otherwise skip*/
            if (isspace(lastInserted))
            {
                if (stringFlag == 1)
                {
                    fputc(buffer, newFile);
                    lastInserted = buffer;
                }
            }
            else
            {
                /*if last inserted is not a white space check if its not inside a []*/
                if (sqBracketsFlag == 0)
                {
                    fputc(buffer, newFile);
                    lastInserted = buffer;
                }
            }
        }
        else
        {
            fputc(buffer, newFile);
            lastInserted = buffer;
        }
        buffer = fgetc(input);
    }
    fclose(newFile);
    return organizedFile;
}
char *getLine(FILE *file)
{
    char buffer;               /*buffer to hold characters from file*/
    int counter = 0;           /*counts the amount of characters in line*/
    char line[MAX_LINE_CHARS]; /*holds the line up to MAX_LINE_CHARS characters*/
    char *returned;
    buffer = fgetc(file);
    while (buffer != EOF && buffer != '\n' && counter < (MAX_LINE_CHARS - 2))
    {
        line[counter] = buffer;
        counter++;
        buffer = fgetc(file);
    }
    if (buffer == EOF)
    {
        if (counter == 0)
        {
            return NULL;
        }
        else
        {
            line[counter] = '\0';
        }
    }
    if (buffer == '\n')
    {
        line[counter] = buffer;
        counter++;
        line[counter] = '\0';
    }
    if (strlen(line) > MAX_LINE_CHARS)
    {
        /*trigger more than MAX_LINE_CHARS characters*/
    }
    returned = (char *)malloc(sizeof(char));
    if (returned == NULL)
    {
        printf("Memory allocation failed.\n");
        exit(0);
    }
    strcpy(returned, line);
    return returned;
}
LinkedList *getTokens(char *line)
{
    int i = 0, firstStringIndex = 0, lastStringIndex = 0, counter = 0;
    char *token;
    LinkedList *tokens = newLinkedList();
    /*go through all the string*/
    if (line[0] == ';')
    {
        return NULL;
    }
    while (line[i] != '\0')
    {
        counter = 0;        /*count characters until SPECIAL character*/
        if (line[i] == '"') /*look for string*/
        {
            firstStringIndex = i;
            while (line[i] != '\0')
            {
                if (line[i] == '"')
                {
                    lastStringIndex = i;
                }
                i++;
            }
            i = lastStringIndex;
            counter = lastStringIndex - firstStringIndex;
        }

        while (isSpecialChar(line[i]) == FALSE)
        {
            counter++;
            i++;
        }

        /*make memory space for token*/
        if (counter > 0)
        {
            token = (char *)malloc(sizeof(char) * (counter + 1));
            /*go back and insert token characters up to SPECIAL character*/
            i = i - counter;
            counter = 0;
            while (isSpecialChar(line[i]) == FALSE)
            {
                token[counter] = line[i];
                counter++;
                i++;
            }
            token[counter] = '\0';
            append(tokens, newNode(token)); /*add token to list*/
        }
        i++; /*skip special character*/
    }
    return tokens;
}
int isSpecialChar(char ch)
{
    if (isspace(ch) == FALSE && ch != '\0' && ch != ',')
    {
        return FALSE;
    }
    else
    {
        return TRUE;
    }
}
void freeTokens(Node *token)
{
    free(token->data);
}
int isMdefine(char *token)
{
    if (strcmp(token, ".define") == 0)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}
int isData(char *token)
{
    if (strcmp(token, ".data") == 0)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}
int isString(char *token)
{
    if (strcmp(token, ".string") == 0)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}
int isExtern(char *token)
{
    if (strcmp(token, ".extern") == 0)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}
int isEntry(char *token)
{
    if (strcmp(token, ".entry") == 0)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

int isString(char *token)
{
    if (strcmp(token, ".string") == 0)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

int isSymbol(char *token)
{
    int i = 0;
    if (isalpha(token[0] == FALSE))
    {
        return FALSE;
    }
    while (token[i + 1] != '\0')
    {
        if (isalnum(token[i] == FALSE))
        {
            return FALSE;
        }
        i++;
    }
    if (token[i] != ':')
    {
        return FALSE;
    }
    return TRUE;
}
