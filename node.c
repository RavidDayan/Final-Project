#include "node.h"

Node *createNode(void *data)
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
