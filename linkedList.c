#include "node.h"
#include "linkedList.h"

void newLinkedList(LinkedList *list);

void append(LinkedList *list, Node *newNode);

void free(LinkedList *list, void (*freeMemory)(Node, int), int type);
