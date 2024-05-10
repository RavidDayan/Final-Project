
#ifndef DATASTRUCTS_H
#define DATASTRUCTS_H

#define MDEFINE 0
#define CODE 1
#define DATA 2
#define MACRO 1
#define MEMORY 2
#define LABEL 3
#define TOKEN 4
#define MEMORY_SIZE 4096


typedef struct Label
{
    char *name;
    int property;
    int value;
} label;

typedef struct Mcro
{
    char *name;
    char *data;
} Mcro;
Mcro *newMcro(char *name);
Mcro *mcroExists(char *newMcro, LinkedList *mcros);

typedef struct LinkedList
{
    Node *head;
} LinkedList;
LinkedList *newLinkedList();
void append(LinkedList *list, Node *newNode);

typedef struct Node
{
    void *data;
    struct Node *next;
} Node;
Node *newNode(void *data);
Node *getNext(Node *node);
void *getData(Node *node);

typedef struct Memory
{
    unsigned short bits : 14; 
} Memory;
void setBits1to2(Memory *data, int number);
void setBits3to4(Memory *data, int number);
void setBits5to6(Memory *data, int number);
void setBits7to10(Memory *data, int number);
void setSignedIntBits3to14(Memory *data, int number);
void setCharBits3to14(Memory *data, char letter);
#endif