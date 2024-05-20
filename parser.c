#include "parser.h"
#include "dataStructs.h"
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "util.h"
#include "errors.h"
#include "MemoryCollector.h"

char *removeWhiteSpace(FILE *input)
{
    FILE *newFile;
    char buffer;
    char *organizedFile = "removeWhiteSpace.as"; /*temporary file to hold proccessed whitespace add/remove .as file*/
    char lastInserted = ' ';                     /*holds the last character that was inserted for comperations to current*/
    int StringEnd = 0;                           /*indicates place for end of string*/
    int counter = 0;
    int sqBracketsFlag = 0; /*indicates chars are currently between brackets*/
    buffer = fgetc(input);
    newFile = fopen(organizedFile, "w");
    while (buffer != EOF)
    {
        if (isSpecialChar(buffer) == TRUE)
        {
            if (buffer == '"') /*insed string all characters are allowed, string is considerd all characters between the most left " and the most right " in a line, each line can hold only 1 string*/
            {
                counter = 0;
                while (buffer != EOF && buffer != '\n') /*find the place of the last " */
                {
                    if (buffer == '"')
                    {
                        StringEnd = counter;
                    }
                    counter++;
                    buffer = fgetc(input);
                }
                fseek(input, -1 * (counter + 1), SEEK_CUR); /*go back to first " */
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
            if (buffer == ':') /*space after : for easier tokening, :[character] is allowed*/
            {
                fputc(buffer, newFile);
                fputc(' ', newFile);
                lastInserted = ' ';
            }
            if (buffer == '[') /*signal start of brackets*/
            {
                fputc(buffer, newFile);
                lastInserted = buffer;
                sqBracketsFlag = 1;
            }
            if (buffer == ']') /*signal end of brackets*/
            {
                fputc(buffer, newFile);
                lastInserted = buffer;
                sqBracketsFlag = 0;
            }
            if (buffer == '=') /*space before and after = for eiasier tokening, char=char is allowed*/
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
            if (buffer == ',') /*remove excess whitespaces before commas*/
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
                if (buffer == '\n' && isspace(lastInserted) != FALSE && lastInserted != '\n') /*remove whitespaces from end of line*/
                {
                    fseek(newFile, -1, SEEK_CUR);
                }
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
    while (buffer != EOF && buffer != '\n' && counter < (MAX_LINE_CHARS - 2)) /*fills the line  up to end of line, eof or 80 characters has reached*/
    {
        line[counter] = buffer;
        counter++;
        buffer = fgetc(file);
    }
    if (buffer == EOF) /*check if we got to end of file*/
    {
        if (counter == 0)
        {
            return NULL;
        }
        else
        {
            buffer = '\n'; /*if a line has been proccessed put \n as l;ast character, file pointer is no on eof,next getline it will return null*/
        }
    }
    if (buffer == '\n') /*add \0 ending*/
    {
        line[counter] = buffer;
        counter++;
        line[counter] = '\0';
    }
    if (strlen(line) > MAX_LINE_CHARS) /*print erroir if line exceeded limit*/
    {
        line[counter] = '\n';
        counter++;
        line[counter] = '\0';
        buffer = fgetc(file);
        while (buffer != '\n' && buffer != EOF)/*skip the line*/
        {
            buffer = fgetc(file);
        }
        errorILegalLineSize(memoryStorage->currentLine, getFT(memoryStorage->as)->name, MAX_LINE_CHARS);
    }
    returned = (char *)malloc(sizeof(char) * (counter + 1));
    if (returned == NULL)
    {
        errorCouldNotAllocateMemory();
    }
    else
    {
        addToCollector(newNode(returned), StringCollector);
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
            counter = lastStringIndex - firstStringIndex; /*find the amount of characters that are in between both ""*/
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
            if (token == NULL)
            {
                errorCouldNotAllocateMemory();
            }
            else
            {
                addToCollector(newNode(token), StringCollector);
            }
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
int isLegalSyntax(char *line, MemoryManager *MM)
{
    char c;
    int i = 0, allowedCommaFlag = FALSE, lastStringChar = 0, closedString = FALSE, decalreFLag = FALSE;
    if (line[0] == ';') /*comment line*/
    {
        return TRUE;
    }
    if (line[0] != '.' && isalpha(line[0]) == FALSE && line[0] != '\n') /* either starts with symbol or .extern/define/data/string/entry*/
    {
        c = line[0];
        errorIlegalCharPlace(MM->currentLine, getFT(MM->as)->name, "of line", "start", c, "'.',';',letter, empty line");
        return FALSE;
    }
    i = 0;
    while (line[i] != '\n')
    {
        if (isIlegalCharacter(line[i]) == TRUE) /* is not a special character outside of a string : , [ ] . # " or alphnum*/
        {
            errorIlegalCharacter(MM->currentLine, getFT(MM->as)->name, line[i]);
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
                errorMissingWord(MM->currentLine, getFT(MM->as)->name, "closing '");
                return FALSE;
            }
            else
            {
                i = lastStringChar;
            }
            i++;
            allowedCommaFlag = TRUE;
            continue;
        }
        if (line[i] == '[') /*handle brackets start to finish with alnum before '[' and end with ']' and only alnum in between []*/
        {
            if (isalnum(line[i - 1]) == FALSE)
            {
                errorIlegalCharPlace(MM->currentLine, getFT(MM->as)->name, "[]", "before", line[i - 1], "letter or integer without spaces");
                return FALSE;
            }
            i++;
            while (line[i] != '\0' && line[i] != ']')
            {
                if (isalnum(line[i]) == FALSE)
                {
                    errorIlegalCharPlace(MM->currentLine, getFT(MM->as)->name, "[]", "inside", line[i], "letter or integer without spaces");
                    return FALSE;
                }
                i++;
            }
            if (line[i] != ']')
            {
                errorIlegalCharPlace(MM->currentLine, getFT(MM->as)->name, "[ + symbol", "after", line[i], "]");

                return FALSE;
            }
            i++;
            allowedCommaFlag = TRUE;
            continue;
        }
        if (line[i] == ']')
        { /*] should be handled in [,otherwise its alone*/
            errorIlegalCharPlace(MM->currentLine, getFT(MM->as)->name, "]", "before", line[i], "[+ symbol");
            return FALSE;
        }
        if (line[i] == ':') /*check alnum before : and no 2 : in line*/
        {
            decalreFLag++;
            if (isalnum(line[i - 1]) == FALSE)
            {
                errorIlegalCharPlace(MM->currentLine, getFT(MM->as)->name, ":", "before", line[i - 1], "letter or integer");
                return FALSE;
            }
            if (decalreFLag == 2)
            {
                errorIlegalWordPlace(MM->currentLine, getFT(MM->as)->name, "after", "symbol decleration", "another decleration", "non decleration");
                return FALSE;
            }
            allowedCommaFlag = FALSE;
        }
        if (line[i] == '=')
        {
            decalreFLag++;
            if (line[i - 1] != ' ' || line[i + 1] != ' ')
            {
                errorIlegalCharPlace(MM->currentLine, getFT(MM->as)->name, " before and after", "=", line[i - 1], "spaces");
                return FALSE;
            }
            allowedCommaFlag = FALSE;
        }
        if (line[i] == '+' || line[i] == '-') /*after +/- must be a number*/
        {
            if (isdigit(line[i + 1]) == FALSE)
            {
                errorIlegalWordPlace(MM->currentLine, getFT(MM->as)->name, "after", "symbol decleration", "another decleration", "non decleration");
                return FALSE;
            }
            allowedCommaFlag = TRUE;
        }
        if (line[i] == '#') /*after # must be a alnum/+/- */
        {
            if (isalnum(line[i + 1]) == FALSE && line[i + 1] != '-' && line[i + 1] != '+')
            {
                errorIlegalCharPlace(MM->currentLine, getFT(MM->as)->name, "#", "after", line[i + 1], "+/-[digit][digit]...");
                return FALSE;
            }
            allowedCommaFlag = TRUE;
        }
        if (line[i] == '.') /*after . must be a alnum/+/- */
        {
            i++;
            if (isalpha(line[i]) == FALSE)
            {
                errorIlegalCharPlace(MM->currentLine, getFT(MM->as)->name, "after", ".", line[i], "data/string/define/extern/entry");
                return FALSE;
            }
            i++;
            while (isalnum(line[i]) != FALSE)
            {
                i++;
            }
            if (isspace(line[i]) == FALSE && line[i] != '\0')
            {
                errorIlegalCharPlace(MM->currentLine, getFT(MM->as)->name, ".operand", "after", line[i], "letter or number");
                return FALSE;
            }
            allowedCommaFlag = FALSE;
            continue;
        }
        if (line[i] == ',') /*cant be 2 consecutive ,*/
        {
            if (allowedCommaFlag == FALSE)
            {
                errorIlegalWordPlace(MM->currentLine, getFT(MM->as)->name, "after", ",", ",", "non consecutive commas");
                return FALSE;
            }
            allowedCommaFlag = FALSE;
        }
        if (line[i] == '_') /*must be between alpphnum*/
        {
            if (isalnum(line[i + 1]) == FALSE || isalnum(line[i - 1]) == FALSE)
            {
                errorIlegalWordPlace(MM->currentLine, getFT(MM->as)->name, " after and before", "_", "non letter or number", "letter or number");
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
int isSavedWord(char *token)
{
    int flag = 0;
    flag = isOpCode(token);
    if (flag != UNDEFINED)
    {
        return TRUE;
    }
    flag = isRegister(token);
    if (flag != UNDEFINED)
    {
        return TRUE;
    }
    if (isEntry(token))
    {
        return TRUE;
    }
    if (isExtern(token))
    {
        return TRUE;
    }
    if (isData(token))
    {
        return TRUE;
    }
    if (isString(token))
    {
        return TRUE;
    }
    if (isMacro(token))
    {
        return TRUE;
    }
    if (isMdefine(token))
    {
        return TRUE;
    }
    return FALSE;
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
    if (token[i] != '-' && token[i] != '+' && isdigit(token[i]) == FALSE)
    {
        return FALSE;
    }
    if (token[i] != '-' || token[i] != '+')
    {
        i++;
    }
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
    if (token[0] == 'r' && isdigit(token[1]) != FALSE && token[2] == '\0')
    {
        charValue = token[1] - '0'; /*digit-'0' results in the the digit itself*/
        if (0 <= charValue && charValue <= 7)
        {
            return charValue;
        }
    }
    return UNDEFINED;
}