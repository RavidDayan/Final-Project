#include "node.h"

typedef struct
{
    Node *head;
} LinkedList;

void newLinkedList(LinkedList *list)
{
    list->head = NULL;
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

void free(LinkedList *list, void (*freeMemory)(Node, int), int type)
{
    Node *current = list->head;
    while (current != NULL)
    {
        Node *temp = current;
        current = current->next;
        freeMemory(temp, type);
    }
    list->head = NULL;
}