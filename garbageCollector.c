#include <stdlib.h>
#include "dataStructs.h"
#include "node.h"
#include "linkedList.h"
void releaseAllFileMemory(LinkedList *mcros, LinkedList *symbols, char *as, char *am, char *ob, char *ext, char *ent)
{
    free(as);
    free(am);
    free(ob);
    free(ext);
    free(ent);
    /*freeList(mcros);
    freeList(symbols)*/
}
void freeList(LinkedList *list, void (*freeData)(Node *))
{
    Node *next;
    Node *current = list->head;
    while (current != NULL)
    {
        next = current->next;
        freeData(current);
        free(current);
        current = next;
    }
    free(list);
}
void freeTokens(Node *token)
{
    free(token->data);
}
void freeMcro(Mcro *mcro)
{
    free(mcro->data);
    free(mcro->name);
    free(mcro);
}