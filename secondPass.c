#include <stdlib.h>
#include "secondPass.h"
#include "util.h"
void secondPass(int ic,char * amFile)
{
    int L=0;
    char *lineBuffer;
    ic = 0; /*1*/
    rewind(amFile);
    while (lineBuffer != NULL) /*2*/
    {
        if (isSymbol(lineBuffer) == FALSE) /*3*/
        {
            if (isData(lineBuffer) != TRUE && isString(lineBuffer) != TRUE && isExtern(lineBuffer) != TRUE) /*4*/
            {
                if (isEntry(lineBuffer) == TRUE) /*5*/
                {
                    /*mark symbols with entry*/ /*6*/
                }
                else
                {
                    /*7*/
                    ic = ic + L; /*8*/
                }
            }
        }
        free(lineBuffer);
    }
    if (errorFlag == TRUE)
    {
        /*handle error*/
    }
    else
    {
        buildFiles();
    }
}