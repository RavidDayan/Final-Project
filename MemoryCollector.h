#include <stdlib.h>
#include "dataStructs.h"
extern MemoryManager *memoryStorage;
extern Node *SymbolCollector;
extern Node *McroCollector;
extern Node *MLCollector;
extern Node *FileTrackerCollector;
extern Node *StringCollector;
extern Node *LLCollector;

void releaseAllFileMemory();
void freeMemoryStorage();
void freeStorageLists();
void freeCollectors();
void freeFiles();
void freeList(LinkedList *list, void (*freeData)(Node *));
void freeCollector(Node *collector, void (*freeData)(Node *));
void freeLinkedList(Node *node);
void freeSymbol(Node *node);
void freeMcro(Node *node);
void freeML(Node *node);
void freeFT(Node *node);
void freeString(Node *node);
void addToCollector(Node *node, Node *collector);