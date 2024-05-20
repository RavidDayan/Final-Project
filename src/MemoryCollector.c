#include <stdlib.h>
#include "../headers/MemoryCollector.h"
#include "../headers/dataStructs.h"
#include "stdio.h"

MemoryManager *memoryStorage = NULL;
Node *SymbolCollector = NULL;
Node *McroCollector = NULL;
Node *MLCollector = NULL;
Node *FileTrackerCollector = NULL;
Node *StringCollector = NULL;
Node *LLCollector = NULL;
/*after freeing,the freed element is set to null*/
/*each freeing function of node types checks that the file has no already been freed(is null)*/
void releaseAllFileMemory()
{
    freeMemoryStorage();
    freeCollectors();
    memoryStorage = NULL;
    remove("removeWhiteSpace.as"); /*incase abrupt exit while pre proccessing emove the helper file*/
}
void freeMemoryStorage()
{
    if (memoryStorage != NULL)
    {
        free(memoryStorage);
    }
    memoryStorage = NULL;
}
void freeCollectors()
{
    freeCollector(SymbolCollector, freeSymbol);
    freeCollector(McroCollector, freeMcro);
    freeCollector(MLCollector, freeML);
    freeCollector(FileTrackerCollector, freeFT);
    freeCollector(StringCollector, freeString);
    freeCollector(LLCollector, freeSymbol);
}
void freeCollector(Node *collector, void (*freeData)(Node *))
{
    Node *node = collector;
    Node *temp;
    while (node != NULL)
    {
        if (node->data != NULL)
        {
            freeData(node);
        }
        temp = node;
        node = getNext(node);
        free(temp);
    }
    collector = NULL;
}
void freeLinkedList(Node *node)
{
    LinkedList *LL = NULL;
    if (node != NULL)
    {
        LL = (LinkedList *)node->data;
    }
    if (LL != NULL)
    {
        free(LL);
        node->data = NULL;
    }
}
void freeSymbol(Node *node)
{
    Symbol *symbol = NULL;
    if (node != NULL)
    {
        symbol = getSymbol(node);
    }
    if (symbol != NULL)
    {
        free(symbol);
        node->data = NULL;
    }
}
void freeMcro(Node *node)
{
    Mcro *mcro = NULL;
    if (node != NULL)
    {
        mcro = getMcr(node);
    }
    if (mcro != NULL)
    {
        free(mcro);
        node->data = NULL;
    }
}
void freeML(Node *node)
{
    MemoryLine *ml = NULL;
    if (node != NULL)
    {
        ml = getML(node);
    }
    if (ml != NULL)
    {
        free(ml);
        node->data = NULL;
    }
}
void freeFT(Node *node)
{
    FileTracker *FT = NULL;
    if (node != NULL)
    {
        FT = getFT(node);

        if (FT != NULL)
        {
            if (FT->file != NULL)
            {
                CloseFile(FT);
                FT->file = NULL;
            }
            free(FT);
            node->data = NULL;
        }
    }
}
void freeString(Node *node)
{
    if (node != NULL)
    {
        if (node->data != NULL)
        {
            free(node->data);
        }
        free(node);
        node->data = NULL;
    }
}
void addToCollector(Node *node, Node *collector)
{
    Node *temp = collector;
    if (temp == NULL)
    {
        collector = node;
    }
    else
    {
        while (getNext(temp) != NULL)
        {
            temp = getNext(temp);
        }
        temp->next = node;
    }
}
