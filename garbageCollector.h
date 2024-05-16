#include <stdlib.h>
#include "dataStructs.h"

void releaseAllFileMemory(LinkedList *mcros, LinkedList *symbols, char *as, char *am, char *ob, char *ext, char *ent);
void freeList(LinkedList *list, void (*freeData)(Node *));
void freeTokens(Node *token);
void freeMcro(Mcro *mcro);
