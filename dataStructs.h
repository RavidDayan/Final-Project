
#ifndef DATASTRUCTS_H
#define DATASTRUCTS_H
#include <stdio.h>
#define MEMORY_SIZE 4096

/*generic node structre to hold data and the next node*/
typedef struct Node
{
    void *data;
    struct Node *next;
} Node;
/*symbol structre to hold symbol name,identifier(mdefine,code...) and value (address of symbol or define of it)*/
typedef struct Symbol
{
    char *name;
    int property;
    int value;
} Symbol;
/*Mcro structre to hold macro name and the contents of the macro*/

typedef struct Mcro
{
    char *name;
    char *data;
} Mcro;
/*linked list structre to hold a pointer to the head of the list and how many elements in the list*/
typedef struct LinkedList
{
    Node *head;
    int size;
} LinkedList;
/*memory line structre to hold direct address of line, source code,binary code,and type(extern,entry,none)*/
typedef struct MemoryLine
{
    int DA;
    Node *SC;
    int BMC;
    int type;
} MemoryLine;
/*Memory manager is a structure used to hold all the counters and instructions , data/code lines ,macro list,symbols list, all input and output files, current line that is proccessed and error flag */
/*this structure serves to hold all the needed data and pass it easily throught the functions*/
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
    int currentLine;
} MemoryManager;
/*file tracker structre to hold file name, if file is open a pointer to it, and the state of the file (open/close))*/
typedef struct FileTracker
{
    char *name;
    FILE *file;
    int state;
} FileTracker;

/*@@@ Symbol functions @@@*/
Symbol *newSymbol(char *name);
Symbol *symbolExists(char *newSymbol, MemoryManager *MM); /*check if symbol already exists and returns it*/
/*@@@ data manipulation*/
int GetArrayData(char *token, MemoryManager *MM);         /*returns the value of symbol[mdefine/digit]*/
char *GetArrayDataSymbol(char *token, MemoryManager *MM); /*returns the symbol inside of []*/
char *getArraySymbol(char *token);                        /*returns the symbol before []*/
char *getSymbolFromDecleration(char *decleration);        /*returns the symbol before :*/
int getRegisterValue(char *token);                        /*returns the value of register*/
int getImidiateValue(char *token, MemoryManager *MM);     /*returns the value of mdefine symbol*/
/*insert lines according to function name*/
void insertMdefine(LinkedList *line, MemoryManager *MM);
void insertExtern(LinkedList *line, MemoryManager *MM);
void insertEntry(LinkedList *line, MemoryManager *MM);
void insertData(LinkedList *line, MemoryManager *MM);
void insertString(LinkedList *line, MemoryManager *MM);
void insertCode(LinkedList *line, MemoryManager *MM);
/*@@@ Macro functions @@@*/
Mcro *newMcro(char *name);
Mcro *mcroExists(char *newMcro, MemoryManager *MM); /*check if mcro already exists and returns it*/
void advanceData(MemoryManager *MM);                /*increases all data memory lines to ic+100*/
/*@@@ Node functions @@@*/
Node *newNode(void *data);
/*return the casted data type of the node*/
Node *getNext(Node *node);
char *getStr(Node *node);
MemoryLine *getML(Node *node);
FileTracker *getFT(Node *node);
Mcro *getMcr(Node *node);
Symbol *getSymbol(Node *node);
/*@@@ Linked list functions @@@*/
LinkedList *newLinkedList();
void append(LinkedList *list, Node *newNode); /*adds node to the end of list*/
/*@@@ Memory Manager @@@*/
MemoryManager *newMemoryManager(char *name);
/*adds */
void AddData(MemoryManager *mm, Node *newData);
void AddCode(MemoryManager *mm, Node *newCode);
void AddMcro(MemoryManager *mm, Node *newMcro);
void AddSymbol(MemoryManager *mm, Node *newSymbol);
void printAll(MemoryManager *MM); /*prints all code lines and symbol table,used for testing*/
/*@@@ File Tracker @@@*/
FileTracker *newFileTracker(char *name);
FILE *openFile(FileTracker *fileTracker, char *type); /*opens file if file is closed and saves a refrence to file or returns pointer to file if it opend,*/
void CloseFile(FileTracker *fileTracker);             /*closes file if file is open only*/
void intializeFiles(MemoryManager *mm, char *name);   /*intializes all memory manager .as,.am,.ob,.ext,.ent file trackers*/
/*@@@ Memory Lines @@@*/
MemoryLine *newMemoryLine(int address);
Node *MLgetAddress(Node *token, MemoryManager *MM, int addressing, int isSrc); /*returns a code/data line with the for the given details about the line */
#endif