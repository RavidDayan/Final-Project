#include "parser.h"
#include "dataStructs.h"
#include "node.h"
#include "linkedList.h"
#include <stdio.h>
#include <ctype.h>
#include <string.h>

FILE *removeWhiteSpace(FILE *input)
{
    FILE *newFile;
    char buffer;
    char lastInserted = ' ';
    int stringFlag = 0;
    int sqBracketsFlag = 0;
    buffer = fgetc(input);
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
                    fputc(buffer, newfile);
                    lastInserted = buffer;
                }
            }
            else
            {
                /*if last inserted is not a white space check if its not inside a []*/
                if (sqBracketsFlag == 0)
                {
                    fputc(buffer, newfile);
                    lastInserted = buffer;
                }
            }
        }
        else
        {
            /*if its not a whitespace check if its not an empty row and insert*/
            if (lastInserted != '\n' || buffer != '\n')
            {
                fputc(buffer, newfile);
                lastInserted = buffer;
            }
        }
        buffer = fgetc(input);
    }
}
char *getLine(FILE *file)
{
    char buffer;               /*buffer to hold characters from file*/
    int counter = 0;           /*counts the amount of characters in line*/
    char line[MAX_LINE_CHARS]; /*holds the line up to MAX_LINE_CHARS characters*/
    int i = 0;
    buffer = fgetc(file);
    while (buffer != EOF && buffer != "\n" && counter <= MAX_LINE_CHARS - 2)
    {
        line[counter] = buffer;
        counter++;
    }
    if (buffer == EOF)
    {
        return NULL;
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
    return line;
}
LinkedList *getTokens(char *line)
{
    int i = 0;
    char *token;
    int counter = 0;
    LinkedList *tokens = newLinkedList();
    /*go through all the string*/
    while (line[i] != '\0')
    { /*count characters until whitespace*/
        while (line[i] != ' ' && line[i] != '\0')
        {
            counter++;
            i++;
        }
        /*make space of token*/
        token = (char *)malloc(sizeof(char) * counter);
        /*go back and insert token characters up to ' '*/
        i = i - counter;
        counter = 0;
        while (line[i] != ' ' && line[i] != '\0')
        {
            token[counter] = line[i];
            i++;
        }
        /*skip ' '*/
        i++;
        /*add token to list*/
        append(tokens, newNode(token));
    }
    return tokens;
}
