#include "parser.h"
#include "dataStructs.h"
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
    int StringEnd = 0, counter = 0;
    int sqBracketsFlag = 0;
    buffer = fgetc(input);
    newFile = fopen(organizedFile, "w");
    while (buffer != EOF)
    {
        if (isSpecialChar(buffer) == TRUE)
        {
            if (buffer == '"') /*handle string*/
            {
                counter = 0;
                while (buffer != EOF && buffer != '\n') /*go back to first ' " '*/
                {
                    if (buffer == '"')
                    {
                        StringEnd = counter;
                    }
                    counter++;
                    buffer = fgetc(input);
                }
                fseek(input, -1 * (counter + 1), SEEK_CUR);
                printf("%c\n", buffer);
                while (StringEnd >= 0)
                {
                    buffer = fgetc(input);
                    fputc(buffer, newFile);
                    StringEnd--;
                }
                buffer = fgetc(input);
                lastInserted = '"';
                continue;
            }
            if (buffer == ':') /*start of brackets*/
            {
                fputc(buffer, newFile);
                fputc(' ', newFile);
                lastInserted = ' ';
            }
            if (buffer == '[') /*start of brackets*/
            {
                fputc(buffer, newFile);
                lastInserted = buffer;
                sqBracketsFlag = 1;
            }
            if (buffer == ']') /*end of brackets*/
            {
                fputc(buffer, newFile);
                lastInserted = buffer;
                sqBracketsFlag = 0;
            }
            if (buffer == '=')
            {
                if (isspace(lastInserted) == FALSE)
                {
                    /*seperate = from both sides*/
                    fputc(' ', newFile);
                    fputc(buffer, newFile);
                    fputc(' ', newFile);
                    lastInserted = ' ';
                }
                else
                {
                    {
                        fputc(buffer, newFile);
                        fputc(' ', newFile);
                        lastInserted = ' ';
                    }
                }
            }
            if (buffer == ',')
            {
                if (isspace(lastInserted) != FALSE)
                {
                    fseek(newFile, -1, SEEK_CUR);
                }
                fputc(buffer, newFile);
                lastInserted = buffer;
            }
        }
        else
        {
            /*check if char is a non \n white space*/
            if (isspace(buffer) && buffer != '\n')
            {
                if (isspace(lastInserted) == FALSE && lastInserted != ',')
                { /*inser whiteSpace only if the character before is not a whitespace*/

                    /*if last inserted is not a white space check if its not inside a []*/
                    if (sqBracketsFlag == FALSE)
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

        while (isTokenSpacer(line[i]) == FALSE)
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
            while (isTokenSpacer(line[i]) == FALSE)
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
int isTokenSpacer(char ch)
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
int isSpecialChar(char ch)
{
    if (ch == ':' || ch == '[' || ch == ']' || ch == '"' || ch == ',' || ch == '=')
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}
int isLegalSyntax(char *line)
{
    int i = 0, allowedCommaFlag = FALSE, lastStringChar = 0, closedString = FALSE, decalreFLag = FALSE;
    if (line[0] == ';') /*comment line*/
    {
        return TRUE;
    }
    if (line[0] != '.' || isalpha(line[0]) == FALSE) /* either starts with symbol or .extern/define/data/string/entry*/
    {
        /*error:ilegal character placement*/
    }
    i = 0;
    while (line[i] != '\n')
    {
        if (isIlegalCharacter(line[i]) == TRUE) /* is not a special character outside of a string : , [ ] . # " or alphnum*/
        {
            /*error:ilegal character*/
            return FALSE;
        }
        if (line[i] == '"') /*handle string from first " to last "*/
        {
            i++;
            while (line[i] != '\0') /*look for string closing "*/
            {
                if (line[i] == '"')
                {
                    lastStringChar = i;
                    closedString = TRUE;
                }
                i++;
            }
            if (closedString == FALSE)
            {
                /*error:missing closing "*/
                return FALSE;
            }
            else
            {
                i = lastStringChar;
            }
            i++;
            allowedCommaFlag = TRUE;
        }
        if (line[i] == '[') /*handle brackets start to finish with alnum before '[' and end with ']' and only alnum in between []*/
        {
            if (isalnum(line[i - 1]) == FALSE)
            {
                /*error:ilegala character before brackets*/
                return FALSE;
            }
            i++;
            while (line[i] != '\0' && line[i] != ']')
            {
                if (isalnum(line[i]) == FALSE)
                {
                    /*error: illegal character in brackets*/
                    return FALSE;
                }
                i++;
            }
            if (line[i] != ']')
            {
                /*error: no closing brackets*/
                return FALSE;
            }
            allowedCommaFlag = TRUE;
        }
        if (line[i] == ']')
        { /*] should be handled in [,otherwise its alone*/
            /*error: no opening brackets*/
            return FALSE;
        }
        if (line[i] == ':') /*check alnum before : and no 2 : in line*/
        {
            decalreFLag++;
            if (isalnum(line[i - 1]) == FALSE)
            {
                /*error: ilegal character before :*/
                return FALSE;
            }
            if (decalreFLag == 2)
            {
                /*error: cannt declare more than once in a line :*/
                return FALSE;
            }
            allowedCommaFlag = FALSE;
        }
        if (line[i] == '+' || line[i] == '-') /*after +/- must be a number*/
        {
            if (isdigit(line[i + 1]) == FALSE)
            {
                /*error: ilegal character after math operand*/
                return FALSE;
            }
            allowedCommaFlag = TRUE;
        }
        if (line[i] == '#') /*after # must be a alnum/+/- */
        {
            if (isalnum(line[i + 1]) == FALSE && isalnum(line[i + 1]) != '-' && isalnum(line[i + 1]) != '+')
            {
                /*error: illegal character after #*/
                return FALSE;
            }
            allowedCommaFlag = TRUE;
        }
        if (line[i] == '.') /*after . must be a alnum/+/- */
        {
            i++;
            if (isalpha(line[i]) == FALSE)
            {
                /*error: illegal character after .*/
                return FALSE;
            }
            i++;
            while (isalnum(line[i]) == TRUE)
            {
                /*error: illegal character after .*/
                return FALSE;
                i++;
            }
            if (isspace(line[i]) == FALSE)
            {
                /*error: missing whitespace after .operation */
                return FALSE;
            }
            allowedCommaFlag = FALSE;
            continue;
        }
        if (line[i] == ',') /*cant be 2 consecutive ,*/
        {
            if (allowedCommaFlag == FALSE)
            {
                /*error:ilegal , placement*/
                return FALSE;
            }
            allowedCommaFlag = FALSE;
        }
        if (line[i] == '_') /*must be between alpphnum*/
        {
            if (isalnum(line[i + 1]) == FALSE || isalnum(line[i - 1]) == FALSE)
            {
                /*error:ilegal character*/
                return FALSE;
            }
        }
        if (isalnum(line[i]) != FALSE) /*allows commas to be placed*/
        {
            allowedCommaFlag = TRUE;
        }
        i++;
    }
    return TRUE;
}
int isIlegalCharacter(char ch)
{
    if (isspace(ch) == FALSE && isalnum(ch) == FALSE && ch != ',' && ch != '=' && ch != ':' && ch != '.' && ch != '#' && ch != '"' && ch != '-' && ch != '+' && ch != '[' && ch != ']' && ch != '_')
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
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
int isInteger(char *token)
{
    int i = 0;
    while (token[i] != '\0')
    {
        if (isdigit(token[i]) == FALSE)
        {
            return FALSE;
        }
        i++;
    }
    return TRUE;
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
int isArray(char *token)
{
    int i = 0;
    while (token[i] != '\0')
    {
        if (token[i] == '[')
        {
            return TRUE;
        }
        i++;
    }
    return FALSE;
}
int isRegister(char *token)
{
    int charValue;
    if (token[0] == 'r' && isdigit(token[1]) == TRUE && token[2] == '\0')
    {
        charValue = token[1];
        if (0 <= charValue - 48 && charValue <= 7)
        {
            return charValue - 48;
        }
    }
    return FALSE;
}