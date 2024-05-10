#include "dataStructs.h"
#include "stdlib.h"
#include "string.h"
#include "stdio.h"

/*@@@ Macro functions @@@*/
Mcro *newMcro(char *name)
{
    Mcro *newMcro = (Mcro *)malloc(sizeof(Mcro));
    if (newMcro == NULL)
    {
        return NULL;
    }
    newMcro->name = (char *)malloc(strlen(name) + 1);
    if (newMcro->name == NULL)
    {
        free(newMcro);
        return NULL;
    }
    strcpy(newMcro->name, name);
    newMcro->data = NULL;
    return newMcro;
}
Mcro *mcroExists(char *newMcro, LinkedList *mcros)
{
    char *mcroName;
    Mcro *mcro;
    Node *mcroNode = mcros->head;
    while (mcroNode != NULL)
    {
        mcro = (Mcro *)mcroNode->data;
        mcroName = mcro->name;
        if (strcmp(newMcro, mcroName) == 0)
        {
            {
                return mcro;
            }
        }
        mcroNode = mcroNode->next;
    }
    return NULL;
}

/*@@@ Node functions @@@*/
Node *newNode(void *data)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (newNode == NULL)
    {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}
Node *getNext(Node *node)
{
    return node->next;
}
void *getData(Node *node)
{
    return node->data;
}

/*@@@ Linked list functions @@@*/
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

/*@@@ Memory functions @@@*/
void setBits1to2(Memory *data, int number) {
    data->bits |= (number & 0b11);
}
void setBits3to4(Memory *data, int number) {
    data->bits |= ((number & 0b11) << 2);
}
void setBits5to6(Memory *data, int number) {
    data->bits |= ((number & 0b11) << 4);
}
void setBits7to10(Memory *data, int number) {
    data->bits |= ((number & 0b1111) << 6);
}
void setSignedIntBits3to14(Memory *data, int number) {
    data->bits |= ((number & 0b1111111111111) << 2);
}
void setCharBits3to14(Memory *data, char letter) {
    data->bits |= ((letter & 0b1111111111111) << 2);
}