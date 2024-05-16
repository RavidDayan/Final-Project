
#ifndef DATASTRUCTS_H
#define DATASTRUCTS_H
#include <stdio.h>
#define MEMORY_SIZE 4096

typedef struct Node
{
    void *data;
    struct Node *next;
} Node;
typedef struct Symbol
{
    char *name;
    int property;
    int value;
} Symbol;
typedef struct Mcro
{
    char *name;
    char *data;
} Mcro;
typedef struct LinkedList
{
    Node *head;
    int size;
} LinkedList;
typedef struct MemoryLine
{
    int DA;
    Node *SC;
    int BMC;
    int type;
} MemoryLine;
typedef struct MemoryManager
{
    Node *code;
    Node *data;
    Node *mcro;
    Node *symbol;
    Node *as;
    Node *am;
    Node *ob;
    Node *ext;
    Node *ent;
    int ic;
    int dc;
    int errorFlag;
} MemoryManager;
typedef struct FileTracker
{
    char *name;
    FILE *file;
    int state;
} FileTracker;
Symbol *newSymbol(char *name);
Symbol *symbolExists(char *newSymbol, MemoryManager *MM);
void insertMdefine(LinkedList *line, MemoryManager *MM);
int GetArrayData(char *token, MemoryManager *MM);
char *getArraySymbol(char *token);
void insertData(LinkedList *line, MemoryManager *MM);
void insertString(LinkedList *line, MemoryManager *MM);
void insertCode(LinkedList *line, MemoryManager *MM);
Mcro *newMcro(char *name);
Mcro *mcroExists(char *newMcro, MemoryManager *MM);

LinkedList *newLinkedList();
void append(LinkedList *list, Node *newNode);

Node *newNode(void *data);
Node *getNext(Node *node);
char *getStr(Node *node);
int getInt(Node *node);
MemoryLine *getML(Node *node);
FileTracker *getFT(Node *node);
Mcro *getMcr(Node *node);
Symbol *getSymbol(Node *node);

MemoryLine *newMemoryLine(int address);
Node *MLgetAddress(Node *token, MemoryManager *MM, int addressing, int isSrc);

MemoryManager *newMemoryManager(char *name);
void AddData(MemoryManager *list, Node *newDataNode);
void AddCode(MemoryManager *list, Node *newCodeNode);
void AddMcro(MemoryManager *list, Node *newMcroNode);
void AddSymbol(MemoryManager *list, Node *newSymbolNode);
FILE *openFile(FileTracker *fileTracker, char *type);
void CloseFile(FileTracker *fileTracker);
void intializeFiles(MemoryManager *mm, char *name);
int isSymbolDefined(char *symbol, MemoryManager *MM);
int getRegisterValue(char *token);
int getImidiateValue(char *token, MemoryManager *MM);

FileTracker *newFileTracker(char *name);
char FTgetName(FileTracker *file);
FILE *FTgetFile(FileTracker *file);
int FTisOpen(FileTracker *file);

#endif