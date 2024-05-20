#ifndef MEMORY_COLLECTOR_H
#define MEMORY_COLLECTOR_H
#include <stdlib.h>
#include "dataStructs.h"
/*holds the MemoryMAnagar of a file the is being proccessd*/
extern MemoryManager *memoryStorage;
/*hold each type of struct of allocated data*/
extern Node *SymbolCollector;
extern Node *McroCollector;
extern Node *MLCollector;
extern Node *FileTrackerCollector;
extern Node *StringCollector;
extern Node *LLCollector;

void releaseAllFileMemory();                                   /*frees all collectors and memory storage*/
void freeMemoryStorage();                                      /*frees memoryStorage*/
void freeCollectors();                                         /*frees all collectors*/
void freeCollector(Node *collector, void (*freeData)(Node *)); /*reicieves collector and matching freeing function of the collectors type,frees all nodes of collector*/
/*frees each type of data node can hold*/
void freeLinkedList(Node *node);
void freeSymbol(Node *node);
void freeMcro(Node *node);
void freeML(Node *node);
void freeFT(Node *node);
void freeString(Node *node);
void addToCollector(Node *node, Node *collector); /*adds node to specific collector*/
#endif