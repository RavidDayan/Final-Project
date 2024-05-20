#include "util.h"
#include <stdlib.h>
#include <string.h>
#include "errors.h"
#include "MemoryCollector.h"
#include "dataStructs.h"
char *addFileEnding(char *fileName, int type)
{
    int endingFlag = FALSE;
    char *newFile;
    if (type == AS)
    {
        newFile = (char *)malloc((strlen(fileName) + 4) * sizeof(char));
        if (newFile == NULL)
        {
            errorCouldNotAllocateMemory();
        }
        else
        {
            addToCollector(newNode(newFile), StringCollector);
        }
        strcat(newFile, fileName);
        strcat(newFile, ".as");
        endingFlag = TRUE;
    }
    if (type == AM)
    {
        newFile = (char *)malloc((strlen(fileName) + 4) * sizeof(char));
        if (newFile == NULL)
        {
            errorCouldNotAllocateMemory();
        }
        else
        {
            addToCollector(newNode(newFile), StringCollector);
        }
        strcat(newFile, fileName);
        strcat(newFile, ".am");
        endingFlag = TRUE;
    }
    if (type == OB)
    {
        newFile = (char *)malloc((strlen(fileName) + 4) * sizeof(char));
        if (newFile == NULL)
        {
            errorCouldNotAllocateMemory();
        }
        else
        {
            addToCollector(newNode(newFile), StringCollector);
        }
        strcat(newFile, fileName);
        strcat(newFile, ".ob");
        endingFlag = TRUE;
    }
    if (type == ENTRY)
    {
        newFile = (char *)malloc((strlen(fileName) + 5) * sizeof(char));
        if (newFile == NULL)
        {
            errorCouldNotAllocateMemory();
        }
        else
        {
            addToCollector(newNode(newFile), StringCollector);
        }
        strcat(newFile, fileName);
        strcat(newFile, ".ent");
        endingFlag = TRUE;
    }
    if (type == EXTERN)
    {
        newFile = (char *)malloc((strlen(fileName) + 5) * sizeof(char));
        if (newFile == NULL)
        {
            errorCouldNotAllocateMemory();
        }
        else
        {
            addToCollector(newNode(newFile), StringCollector);
        }
        strcat(newFile, fileName);
        strcat(newFile, ".ext");
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
    int multiplyer = 1; /*multiplier for + or - integer*/
    int decimal = 1;
    int numbeValue = 0;
    int result = 0;
    if (number == NULL || *number == '\0' || (number[0] != '+' && number[0] != '-' && isdigit(number[0]) == FALSE)) /*number must start with + - or digit*/
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
    while (number[i] != '\0') /*check that all characters are digits*/
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
    while (counter > 0) /*go from the end to the start and mutiply digit by the appropriate decimal */
    {
        numbeValue = number[i] - '0';
        result = (numbeValue * decimal) + result;
        decimal = decimal * 10;
        counter--;
        i--;
    }
    *success = TRUE;
    return result * multiplyer;
}
int legalInteger(int num)
{
    if ((MIN_INT_SIZE * -1) <= num && num <= MAX_INT_SIZE)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}