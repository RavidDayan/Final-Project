#include "util.h"
#include <stdlib.h>
#include <string.h>
char *addFileEnding(char *fileName, int type)
{
    int endingFlag = FALSE;
    char *newFile;
    if (type == AS)
    {
        newFile = (char *)malloc((strlen(fileName) + 4) * sizeof(char));
        strcat(newFile, fileName);
        strcat(newFile, ".as");
        endingFlag = TRUE;
    }
    if (type == AM)
    {
        newFile = (char *)malloc((strlen(fileName) + 4) * sizeof(char));
       strcat(newFile, fileName);
        strcat(newFile, ".am");
        endingFlag = TRUE;
    }
    if (type == OB)
    {
        newFile = (char *)malloc((strlen(fileName) + 4) * sizeof(char));
        strcat(newFile, fileName);
        strcat(fileName, ".ob");
        endingFlag = TRUE;
    }
    if (type == EXT)
    {
        newFile = (char *)malloc((strlen(fileName) + 5) * sizeof(char));
        strcat(newFile, fileName);
        strcat(fileName, ".ent");
        endingFlag = TRUE;
    }
    if (type == ENT)
    {
        newFile = (char *)malloc((strlen(fileName) + 5) * sizeof(char));
        strcat(newFile, fileName);
        strcat(fileName, ".ext");
        endingFlag = TRUE;
    }
    if (endingFlag == TRUE)
    {
        return newFile;
    }
    else
    {
        return NULL;
    }
}
int stringToInt(char *number, int *success)
{
    int counter = 0;
    int i = 0;
    int multiplyer = 1;
    int decimal = 1;
    int numbeValue=0;
    int result=0;
    if (number == NULL || *number == '\0' || (number[0] != '+' && number[0] != '-' && isdigit(number[0]) == FALSE))
    {
        *success = FALSE;
        return 0;
    }
    if (number[0] == '-')
    {
        multiplyer = -1;
        i++;
    }
    if (number[0] == '+')
    {
        multiplyer = 1;
        i++;
    }
    while (number[i] != '\0')
    {
        if (isdigit(number[i]) == FALSE)
        {
            *success = FALSE;
            return 0;
        }
        counter++;
        i++;
    }
    i--;
    while (counter > 0)
    {
        numbeValue=number[i]-'0';
        result = (numbeValue * decimal) + result;
        decimal = decimal * 10;
        counter--;
        i--;
    }
    *success = TRUE;
    return result * multiplyer;
}