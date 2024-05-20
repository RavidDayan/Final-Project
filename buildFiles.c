#include "dataStructs.h"
#include "binary.h"
#include "stdio.h"
#include "string.h"
#include "util.h"
#include "errors.h"
void buildFiles(MemoryManager *MM)
{
    FILE *ob = NULL, *ext = NULL, *ent = NULL;
    int counter = 0, openFlag = FALSE; /*counter:counts lines of code in a file,openFlag:signals file has been opend*/
    /*holders*/
    Symbol *symbol;
    Node *data;
    Node *symbols;
    MemoryLine *ML;
    /*write .ob*/
    ob = openFile(getFT(MM->ob), "w");
    if (ob == NULL)
    {
        errorCouldNotOpenFile(getFT(MM->ob)->name);
    }
    data = MM->code;
    /*count code lines*/
    while (data != NULL)
    {
        counter++;
        data = getNext(data);
    }
    fprintf(ob, "%d", counter);
    /*count data lines*/
    counter = 0;
    data = MM->data;
    while (data != NULL)
    {
        counter++;
        data = getNext(data);
    }
    fprintf(ob, " %d\n", counter);
    /*insert hashed qauntinary code lines into .ob*/
    data = MM->code;
    while (data != NULL)
    {
        ML = getML(data);
        /*compensate for addresses smaller than 1000 to have the first digit as 0,139->0139*/
        if (ML->DA < 1000)
        {
            fputc('0', ob);
        }
        fprintf(ob, "%d ", ML->DA);
        binToQuantPrint(ML->BMC, ob);
        data = getNext(data);
    }
    /*insert hashed qauntinary data lines into .ob*/

    data = MM->data;
    while (data != NULL)
    {
        ML = getML(data);
        if (ML->DA < 1000)
        {
            fputc('0', ob);
        }
        fprintf(ob, "%d ", ML->DA);
        binToQuantPrint(ML->BMC, ob);
        data = getNext(data);
    }
    /*insert all lines that are extern into .ext*/

    data = MM->symbol;
    openFlag = FALSE;
    while (data != NULL)
    {
        symbol = getSymbol(data);
        if (symbol->property == EXTERN)
        {
            symbols = MM->code;
            while (symbols != NULL)
            {
                ML = getML(symbols);
                if (strcmp(getStr(ML->SC), symbol->name) == 0)
                { /*opens file .ext only if there is at least 1 ext line*/
                    if (openFlag == FALSE)
                    {
                        openFlag = TRUE;
                        ext = openFile(getFT(MM->ext), "w");
                    }
                    fprintf(ext, "%s ", getStr(ML->SC));
                    if (ML->DA < 1000)
                    {
                        fputc('0', ext);
                    }
                    fprintf(ext, "%d\n", ML->DA);
                }
                symbols = getNext(symbols);
            }
        }

        data = getNext(data);
    }
    /*insert all lines that are entry into .ext*/
    data = MM->symbol;
    openFlag = FALSE;

    while (data != NULL)
    {
        symbol = getSymbol(data);
        if (symbol->property == ENTRY)
        {
            if (openFlag == FALSE)
            {
                openFlag = TRUE;
                ent = openFile(getFT(MM->ent), "w");
            }
            fprintf(ent, "%s ", symbol->name);
            if (symbol->value < 1000)
            {
                fputc('0', ent);
            }
            fprintf(ent, "%d\n", symbol->value);
        }
        data = getNext(data);
    }
}