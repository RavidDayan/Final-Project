#include "node.h"
#include "linkedList.h"
#include "stdlib.h"
#include "stdio.h"

LinkedList *newLinkedList()
{
    LinkedList *newLinkedList = (LinkedList *)malloc(sizeof(newLinkedList));
    if (newLinkedList == NULL)
    {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    newLinkedList->head = NULL;
    return newLinkedList;
}

void append(LinkedList *list, Node *newNode)
{
    Node *current = list->head;
    if (current == NULL)
    {
        list->head = newNode;
    }
    else
    {
        while (current->next != NULL)
        {
            current = current->next;
        }
        current->next = newNode;
    }
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