#include "dataStructs.h"
#include "binary.h"
#include "stdio.h"
#include "string.h"
#include "util.h"
#include "errors.h"
void buildFiles(MemoryManager *MM)
{
    FILE *ob = NULL, *ext = NULL, *ent = NULL;
    int counter = 0, openFlag = FALSE;
    Symbol *symbol;
    Node *data;
    Node *symbols;
    MemoryLine *ML;
    ob = openFile(getFT(MM->ob), "w");
    if (ob == NULL)
    {
        errorCouldNotOpenFile(getFT(MM->ob)->name);
    }
    data = MM->code;
    while (data != NULL)
    {
        counter++;
        data = getNext(data);
    }
    fprintf(ob, "%d", counter);
    counter = 0;
    data = MM->data;
    while (data != NULL)
    {
        counter++;
        data = getNext(data);
    }
    fprintf(ob, " %d\n", counter);
    data = MM->code;
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
                {
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