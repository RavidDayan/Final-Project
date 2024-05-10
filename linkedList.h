#ifndef LINKED_LIST_H
#define LINKED_LIST_H
#include "node.h"

typedef struct LinkedList
{
    Node *head;
} LinkedList;

LinkedList *newLinkedList();

void append(LinkedList *list, Node *newNode);

void freeList(LinkedList *list, void (*freeData)(Node *));
#endif
