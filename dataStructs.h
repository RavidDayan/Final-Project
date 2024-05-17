
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

/*@@@ Symbol functions @@@*/
Symbol *newSymbol(char *name);
Symbol *symbolExists(char *newSymbol, MemoryManager *MM);
/*@@@ data manipulation*/
void insertMdefine(LinkedList *line, MemoryManager *MM);
void insertExtern(LinkedList *line, MemoryManager *MM);
void insertEntry(LinkedList *line, MemoryManager *MM);
int GetArrayData(char *token, MemoryManager *MM);
char * GetArrayDataSymbol(char *token, MemoryManager *MM);
char *getArraySymbol(char *token);
char *getSymbolFromDecleration(char* decleration);
void insertData(LinkedList *line, MemoryManager *MM);
void insertString(LinkedList *line, MemoryManager *MM);
void insertCode(LinkedList *line, MemoryManager *MM);
/*@@@ Macro functions @@@*/
Mcro *newMcro(char *name);
Mcro *mcroExists(char *newMcro, MemoryManager *MM);
void advanceData(MemoryManager *MM);
/*@@@ Node functions @@@*/
Node *newNode(void *data);
Node *getNext(Node *node);
char *getStr(Node *node);
int getInt(Node *node);
MemoryLine *getML(Node *node);
FileTracker *getFT(Node *node);
Mcro *getMcr(Node *node);
Symbol *getSymbol(Node *node);
/*@@@ Linked list functions @@@*/
LinkedList *newLinkedList();
void append(LinkedList *list, Node *newNode);
/*@@@ Memory Manager @@@*/
MemoryManager *newMemoryManager(char *name);
void AddData(MemoryManager *mm, Node *newData);
void AddCode(MemoryManager *mm, Node *newCode);
void AddMcro(MemoryManager *mm, Node *newMcro);
void AddSymbol(MemoryManager *mm, Node *newSymbol);
int getRegisterValue(char *token);
int getImidiateValue(char *token, MemoryManager *MM);
void printAll(MemoryManager *MM);
/*@@@ File Tracker @@@*/
FileTracker *newFileTracker(char *name);
FILE *openFile(FileTracker *fileTracker, char *type);
void CloseFile(FileTracker *fileTracker);
void intializeFiles(MemoryManager *mm, char *name);
int isSymbolDefined(char *token, MemoryManager *MM);
/*@@@ Memory Lines @@@*/
MemoryLine *newMemoryLine(int address);
Node *MLgetAddress(Node *token, MemoryManager *MM, int addressing, int isSrc);

#endif