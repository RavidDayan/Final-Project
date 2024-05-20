#include "dataStructs.h"
#include "stdlib.h"
#include "ctype.h"
#include "string.h"
#include "stdio.h"
#include "util.h"
#include "parser.h"
#include "opcode.h"
#include "binary.h"
#include "errors.h"
#include "MemoryCollector.h"
/*each newtype function saved the memory pointer to the apropriate collector*/
/*@@@ Node functions @@@*/
Node *newNode(void *data)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (newNode == NULL)
    {
        errorCouldNotAllocateMemory();
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}
Node *getNext(Node *node)
{
    if (node != NULL)
    {
        return node->next;
    }
    return NULL;
}
char *getStr(Node *node)
{
    return (char *)node->data;
}
MemoryLine *getML(Node *node)
{
    return (MemoryLine *)(node->data);
}
FileTracker *getFT(Node *node)
{
    return (FileTracker *)(node->data);
}
Mcro *getMcr(Node *node)
{
    return (Mcro *)node->data;
}
Symbol *getSymbol(Node *node)
{
    return (Symbol *)node->data;
}
/*@@@ Symbol functions @@@*/
Symbol *newSymbol(char *name)
{
    Symbol *newSymbol = (Symbol *)malloc(sizeof(Symbol));
    if (newSymbol == NULL)
    {
        errorCouldNotAllocateMemory();
    }
    else
    {
        addToCollector(newNode(newSymbol), SymbolCollector);
    }
    newSymbol->name = (char *)malloc(sizeof(char) * (sizeof(name) + 1));
    if (newSymbol->name == NULL)
    {
        errorCouldNotAllocateMemory();
    }
    else
    {
        addToCollector(newNode(newSymbol->name), StringCollector);
    }
    strcpy(newSymbol->name, name);
    newSymbol->property = UNDEFINED;
    newSymbol->value = 0;
    return newSymbol;
}
Symbol *symbolExists(char *newSymbol, MemoryManager *MM)
{
    Symbol *symbol;
    Node *symbolNode = MM->symbol;
    while (symbolNode != NULL) /*look for matching symbol*/
    {
        symbol = getSymbol(symbolNode);
        if (strcmp(getSymbolFromDecleration(newSymbol), getSymbolFromDecleration(symbol->name)) == 0)
        {
            {
                return symbol;
            }
        }
        symbolNode = getNext(symbolNode);
    }
    return NULL;
}
/*@@@ data manipulation*/
int GetArrayData(char *token, MemoryManager *MM)
{
    char *symbol;
    Symbol *value;
    int labelFlag = 0;
    int i = 0, flag = FALSE, counter = 0, success = FALSE;
    while (token[i] != '\0') /*count how manay characters are inside []*/
    {
        if (token[i] == ']')
        {
            flag = FALSE;
        }
        if (flag == TRUE)
        {
            if (isdigit(token[i]) == FALSE)
            {
                labelFlag = TRUE;
            }
            counter++;
        }
        if (token[i] == '[')
        {
            flag = TRUE;
        }
        i++;
    }
    symbol = (char *)malloc(sizeof(char) * (counter + 1));
    if (symbol == NULL)
    {
        errorCouldNotAllocateMemory();
    }
    else
    {
        addToCollector(newNode(symbol), StringCollector);
    }
    counter = 0;
    i = 0;
    while (token[i] != '\0') /*insert character inside [] to alocated memory*/
    {
        if (token[i] == ']')
        {
            flag = FALSE;
        }

        if (flag == TRUE)
        {
            symbol[counter] = token[i];
            counter++;
        }
        if (token[i] == '[')
        {
            flag = TRUE;
        }

        i++;
    }
    symbol[counter] = '\0';
    if (labelFlag == TRUE) /*check */
    {
        value = symbolExists(symbol, MM); /*look for symbol value*/
        if (value == NULL)
        {
            errorMissingDecleration(MM->currentLine, getFT(MM->as)->name, symbol);
            MM->errorFlag = TRUE;
        }
        else
        {
            return value->value;
        }
    }
    else /*if no value was found try to see if its a number*/
    {
        i = stringToInt(symbol, &success);
        if (success == TRUE)
        {
            if (legalInteger(i) == TRUE)
            {
                return i;
            }
            else
            {
                errorIlegalInteger(MM->currentLine, getFT(MM->as)->name, symbol);
            }
        }
        else
        {
            errorMissingDecleration(MM->currentLine, getFT(MM->as)->name, symbol);
            MM->errorFlag = TRUE;
        }
    }
    return UNDEFINED;
}
char *GetArrayDataSymbol(char *token, MemoryManager *MM)
{
    char *symbol;
    int i = 0, flag = FALSE, counter = 0;
    while (token[i] != '\0') /*count characters between []*/
    {
        if (token[i] == ']')
        {
            flag = FALSE;
        }
        if (flag == TRUE)
        {
            counter++;
        }
        if (token[i] == '[')
        {
            flag = TRUE;
        }
        i++;
    }
    symbol = (char *)malloc(sizeof(char) * (counter + 1));
    if (symbol == NULL)
    {
        errorCouldNotAllocateMemory();
    }
    else
    {
        addToCollector(newNode(symbol), StringCollector);
    }
    counter = 0;
    i = 0;
    while (token[i] != '\0') /*add characters between [] to allocated memory*/
    {
        if (token[i] == ']')
        {
            flag = FALSE;
        }
        if (flag == TRUE)
        {
            symbol[counter] = token[i];
            counter++;
        }
        if (token[i] == '[')
        {
            flag = TRUE;
        }

        i++;
    }
    symbol[counter] = '\0';
    return symbol;
}
char *getArraySymbol(char *token)
{
    char *symbol;
    int i = 0;
    while (token[i] != '[') /*count characters before []*/
    {
        i++;
    }
    symbol = (char *)malloc(sizeof(char) * (i + 1));
    if (symbol == NULL)
    {
        errorCouldNotAllocateMemory();
    }
    else
    {
        addToCollector(newNode(symbol), StringCollector);
    }
    i = 0;
    while (token[i] != '[') /*add characters before [] to allocated memory*/
    {
        symbol[i] = token[i];
        i++;
    }
    symbol[i] = '\0';
    return symbol;
}
char *getSymbolFromDecleration(char *decleration)
{
    int i = 0;
    char *symbol = NULL;
    while (isalnum(decleration[i]) != 0) /*count characters that are alnum*/
    {
        i++;
    }
    symbol = (char *)malloc(sizeof(char) * (i + 1));
    if (symbol == NULL)
    {
        errorCouldNotAllocateMemory();
    }
    else
    {
        addToCollector(newNode(symbol), StringCollector);
    }
    i = 0;
    while (isalnum(decleration[i]) != 0) /*add alnum characters to allocated memory*/
    {
        symbol[i] = decleration[i];
        i++;
    }
    symbol[i] = '\0';
    return symbol;
}
void insertMdefine(LinkedList *line, MemoryManager *MM)
{
    /*define structure [.define,symbol,=,int]*/
    Node *token = line->head, *symbol = MM->symbol;
    Symbol *newMdefine;
    char *symbolName;
    int succesfullConverted = FALSE, number = UNDEFINED;
    if (line->size != 4)
    {
        errorIlegalWordCount(MM->currentLine, getFT(MM->as)->name, getStr(token));
        MM->errorFlag = TRUE;
        return;
    }
    else
    {
        token = getNext(token); /*symbol name*/
        symbolName = getStr(token);
        if (isalpha(getStr(token)[0])) /*check that symbol starts with a letter*/
        {
            if (symbolExists(symbolName, MM) == NULL) /*check that symbol does not exist*/
            {
                if (mcroExists(symbolName, MM) == NULL) /*check that symbol is not a macro name*/
                {
                    if (isSavedWord(symbolName) == FALSE)
                    {
                        token = getNext(token); /*operand '='*/
                        if (strcmp(getStr(token), "=") == 0)
                        {
                            token = getNext(token); /*number*/
                            number = stringToInt(getStr(token), &succesfullConverted);
                            if (succesfullConverted == TRUE && legalInteger(number) == TRUE) /*check for legal integer*/
                            {
                                newMdefine = newSymbol(symbolName);
                                newMdefine->property = MDEFINE;
                                newMdefine->value = number;
                                symbol = newNode(newMdefine);
                                AddSymbol(MM, symbol);
                            }
                            else
                            {
                                errorIlegalInteger(MM->currentLine, getFT(MM->as)->name, getStr(token));
                                MM->errorFlag = TRUE;
                                return;
                            }
                        }
                        else
                        {
                            errorMissingWord(MM->currentLine, getFT(MM->as)->name, "=");
                            MM->errorFlag = TRUE;
                            return;
                        }
                    }
                    else
                    {
                        errorIsSavedWord(MM->currentLine, getFT(MM->as)->name, symbolName);
                        MM->errorFlag = TRUE;
                        return;
                    }
                }
                else
                {
                    errorDuplicateMacro(MM->currentLine, getFT(MM->as)->name, symbolName);
                    MM->errorFlag = TRUE;
                    return;
                }
            }
            else
            {
                errorDuplicateSymbol(MM->currentLine, getFT(MM->as)->name, symbolName);
                MM->errorFlag = TRUE;
                return;
            }
        }
        else
        {
            errorIlegalLabel(MM->currentLine, getFT(MM->as)->name, getStr(token));
            MM->errorFlag = TRUE;
            return;
        }
    }
}
void insertExtern(LinkedList *line, MemoryManager *MM)
{
    Node *token = line->head;
    Symbol *symbol;
    if (line->size != 2) /*extern should have only 2 words .extern label*/
    {
        errorIlegalWordCount(MM->currentLine, getFT(MM->as)->name, "extern");
        MM->errorFlag = TRUE;
        return;
    }
    token = getNext(token);
    symbol = symbolExists(getStr(token), MM);
    if (symbol != NULL) /*check if symbol with same name exists*/
    {
        errorDuplicateSymbol(MM->currentLine, getFT(MM->as)->name, getStr(token));
        MM->errorFlag = TRUE;
        return;
    }
    else
    {
        if (mcroExists(getStr(token), MM) == NULL) /*check that symbol is not a macro name*/
        {
            if (isSavedWord(getStr(token)) == FALSE)
            {
                symbol = newSymbol(getStr(token));
                symbol->property = EXTERN;
                symbol->value = 0;
                AddSymbol(MM, newNode(symbol));
            }
            else
            {
                errorIsSavedWord(MM->currentLine, getFT(MM->as)->name, getStr(token));
                MM->errorFlag = TRUE;
                return;
            }
        }
        else
        {
            errorDuplicateMacro(MM->currentLine, getFT(MM->as)->name, getStr(token));
            MM->errorFlag = TRUE;
            return;
        }
    }
}
void insertEntry(LinkedList *line, MemoryManager *MM)
{
    Node *token = line->head;
    Symbol *symbol;
    if (line->size != 2) /*entry should have only 2 words .extern label*/
    {
        errorIlegalWordCount(MM->currentLine, getFT(MM->as)->name, "entry");
        MM->errorFlag = TRUE;
        return;
    }
    else
    {
        token = getNext(token);
        symbol = symbolExists(getStr(token), MM); /*look for symbol in symbol tables*/
        if (symbol != NULL)
        {
            if (symbol->property != EXTERN)
            {
                symbol->property = ENTRY;
            }
            else
            {
                errorCouldNotSetEntry(MM->currentLine, getFT(MM->as)->name, getStr(token));
                MM->errorFlag = TRUE;
                return;
            }
        }
        else
        {
            errorMissingDecleration(MM->currentLine, getFT(MM->as)->name, getStr(token));
            MM->errorFlag = TRUE;
            return;
        }
    }
}
void insertData(LinkedList *line, MemoryManager *MM)
{
    /*data structure [label:,.data,[int/symbol]]*/
    Node *token = line->head;
    Symbol *symbol;
    MemoryLine *ML;
    char *arraySymbol, *symbolName;
    int number;
    int succesfullConverted = FALSE;
    int firstDigit = TRUE; /*incicates the source code has been entered to the first digit*/
    symbolName = getSymbolFromDecleration(getStr(token));
    if (symbolExists(symbolName, MM) == NULL) /*check that symbol is duplicate*/
    {
        if (mcroExists(symbolName, MM) == NULL) /*check that symbol is not a macro name*/
        {
            if (isSavedWord(symbolName) == FALSE)
            {
                /*insert new symbol*/
                symbol = newSymbol(getSymbolFromDecleration(getStr(token)));
                symbol->property = DATA;
                symbol->value = MM->dc;
                AddSymbol(MM, newNode(symbol));
                /*skip .data*/
                token = getNext(token);
                token = getNext(token);
                /*insert data*/
                while (token != NULL)
                { /*check if data is a number or symbol*/
                    if (isInteger(getStr(token)) == FALSE)
                    {
                        /*check if symbol is defined or array*/
                        if ((symbol = symbolExists(getStr(token), MM)) != NULL) /*is it a known symbol?*/
                        {
                            if (symbol->property == MDEFINE || symbol->property == EXTERN) /*check if its mdefined or extern*/
                            {
                                number = symbol->value;
                                MM->dc = MM->dc + 1;
                                ML = newMemoryLine(MM->dc);
                                ML->BMC = number;
                            }
                            else
                            {
                                errorIlegalWordPlace(MM->currentLine, getFT(MM->as)->name, "data", "When entering", "not mdefine or extern", "mdefine or exter");
                                MM->errorFlag = TRUE;
                                return;
                            }
                        }
                        else
                        {
                            if (isArray(getStr(token)) == TRUE) /*is it an array?*/
                            {
                                arraySymbol = getArraySymbol(getStr(token));
                                symbol = symbolExists(arraySymbol, MM);
                                if (symbol != NULL) /*if array symbol already declared use the address else unspecficy address*/
                                {
                                    MM->dc = MM->dc + 1;
                                    ML = newMemoryLine(MM->dc);
                                    ML->BMC = symbol->value;
                                }
                                else
                                {
                                    MM->dc = MM->dc + 1;
                                    ML = newMemoryLine(MM->dc);
                                    ML->BMC = UNDEFINED;
                                    ML->SC = newNode(arraySymbol);
                                }
                                number = GetArrayData(getStr(token), MM); /*get the value of the adress inside the array*/
                                if (number == UNDEFINED)
                                {
                                    MM->errorFlag = TRUE;
                                    return;
                                }
                                else
                                {
                                    MM->dc = MM->dc + 1;
                                    ML = newMemoryLine(MM->dc);
                                    ML->BMC = number;
                                    ML->SC = newNode(arraySymbol);
                                }
                            }
                            else
                            {
                                errorMissingDecleration(MM->currentLine, getFT(MM->as)->name, getStr(token));
                                MM->errorFlag = TRUE;
                                return;
                            }
                        }
                    }
                    else /*not a symbol , check if its is a digit*/
                    {
                        number = stringToInt(getStr(token), &succesfullConverted);
                        if (succesfullConverted == FALSE)
                        {
                            errorMissingDecleration(MM->currentLine, getFT(MM->as)->name, getStr(token));
                            MM->errorFlag = TRUE;
                            return;
                        }
                        if (legalInteger(number) == FALSE)
                        {
                            errorIlegalInteger(MM->currentLine, getFT(MM->as)->name, getStr(token));
                            MM->errorFlag = TRUE;
                            return;
                        }
                        MM->dc = MM->dc + 1;
                        ML = newMemoryLine(MM->dc);
                        ML->BMC = number;
                    }
                    if (firstDigit) /*is it the first line of .data?*/
                    {
                        ML->SC = line->head;
                        firstDigit = FALSE;
                    }
                    else
                    {
                        ML->SC = NULL;
                    }
                    AddData(MM, newNode(ML));
                    token = getNext(token);
                }
            }
            else
            {
                errorIsSavedWord(MM->currentLine, getFT(MM->as)->name, symbolName);
                MM->errorFlag = TRUE;
                return;
            }
        }
        else
        {
            errorDuplicateMacro(MM->currentLine, getFT(MM->as)->name, symbolName);
            MM->errorFlag = TRUE;
            return;
        }
    }
    else /*print error if duplicate*/
    {
        errorDuplicateSymbol(MM->currentLine, getFT(MM->as)->name, getStr(token));
        MM->errorFlag = TRUE;
        return;
    }
}
void insertString(LinkedList *line, MemoryManager *MM)
{
    /*data structure [label:,.data,[int/symbol]]*/
    Node *token = line->head;
    Symbol *symbol;
    MemoryLine *ML;
    char *string, *symbolName;
    int i = 0;
    symbolName = getSymbolFromDecleration(getStr(token));
    if (symbolExists(symbolName, MM) == NULL) /*check that symbol isent duplicate*/
    {
        if (mcroExists(symbolName, MM) == NULL) /*check that symbol is not a macro name*/
        {
            if (isSavedWord(symbolName) == FALSE)
            {
                /*insert new symbol*/
                symbol = newSymbol(getSymbolFromDecleration(getStr(token)));
                symbol->property = STRING;
                symbol->value = MM->dc;
                AddSymbol(MM, newNode(symbol));
                /*skip .string*/
                token = getNext(token);
                token = getNext(token);
                /*insert chars*/
                string = getStr(token);
                if (string[i] != '"') /*first char should be "*/
                {
                    errorMissingWord(MM->currentLine, getFT(MM->as)->name, "''");
                    MM->errorFlag = TRUE;
                    return;
                }
                else
                {
                    for (i = 1; i < strlen(string) - 1; i++) /*get chars up to last  "*/
                    {
                        MM->dc = MM->dc + 1;
                        ML = newMemoryLine(MM->dc);
                        ML->BMC = string[i];
                        if (i == 0)
                        {
                            ML->SC = NULL;
                        }
                        else
                        {
                            ML->SC = NULL;
                        }
                        AddData(MM, newNode(ML));
                    }
                    MM->dc = MM->dc + 1;
                    ML = newMemoryLine(MM->dc);
                    ML->BMC = 0;
                    ML->SC = newNode("\0");
                    AddData(MM, newNode(ML));
                }
            }
            else
            {
                errorIsSavedWord(MM->currentLine, getFT(MM->as)->name, symbolName);
                MM->errorFlag = TRUE;
                return;
            }
        }
        else
        {
            errorDuplicateMacro(MM->currentLine, getFT(MM->as)->name, symbolName);
            MM->errorFlag = TRUE;
            return;
        }
    }
    else
    {
        errorDuplicateSymbol(MM->currentLine, getFT(MM->as)->name, getStr(token));
        MM->errorFlag = TRUE;
        return;
    }
}
void insertCode(LinkedList *line, MemoryManager *MM)
{
    Node *token = line->head, *firstMLline = NULL, *srcNode = NULL, *desNode = NULL, *TempNode;
    Symbol *symbol;
    MemoryLine *tempML;
    char *tempString, *symbolName;
    int symbolFlag = 0;
    int opcode = UNDEFINED;
    int src = 0;
    int des = 0;
    /*check if theres a symbol at the start*/
    if (isSymbol(getStr(token)))
    {
        symbolName = getSymbolFromDecleration(getStr(token));
        symbol = symbolExists(symbolName, MM);
        if (symbol != NULL) /*check if symbol already exists*/
        {
            errorDuplicateSymbol(MM->currentLine, getFT(MM->as)->name, getStr(token));
            MM->errorFlag = TRUE;
            return;
        }
        else
        {
            if (mcroExists(symbolName, MM) == NULL) /*check that symbol is not a macro name*/
            {
                if (isSavedWord(symbolName) == FALSE)
                {
                    symbolFlag = TRUE;
                    tempString = getSymbolFromDecleration(getStr(token));
                    symbol = newSymbol(tempString);
                    symbol->property = CODE;
                    symbol->value = MM->ic + STARTING_ADDRESS;
                    AddSymbol(MM, newNode(symbol));
                    token = getNext(token);
                }
                else
                {
                    errorIsSavedWord(MM->currentLine, getFT(MM->as)->name, symbolName);
                    MM->errorFlag = TRUE;
                    return;
                }
            }
            else
            {
                errorDuplicateMacro(MM->currentLine, getFT(MM->as)->name, symbolName);
                MM->errorFlag = TRUE;
                return;
            }
        }
    }
    opcode = isOpCode(getStr(token));
    if (opcode != UNDEFINED)
    {
        if (enoughOperands((line->size) - (1 + symbolFlag), opcode) == TRUE) /*does line have enough operands for the operation code*/
        {
            tempML = newMemoryLine(MM->ic + STARTING_ADDRESS);
            tempML->SC = line->head;
            tempML->BMC = setCode(0, opcode);
            firstMLline = newNode(tempML);
            if ((line->size) - (1 + symbolFlag) == 1) /*1 operand needed*/
            {
                token = getNext(token);
                des = getAddressingCode(getStr(token));
                if (legalDesOp(des, opcode) == TRUE) /*check if operand type is legal for this operation*/
                {
                    srcNode = MLgetAddress(token, MM, des, FALSE); /*put into src because in in the end source code is label->opcode->src->des*/
                }
                else
                {
                    errorILegalAddressing(MM->currentLine, getFT(MM->as)->name, getStr(token), "des");
                    MM->errorFlag = TRUE;
                    return;
                }
            }
            if ((line->size) - (1 + symbolFlag) == 2) /*2 operand needed*/
            {
                token = getNext(token);
                src = getAddressingCode(getStr(token));
                srcNode = token;
                token = getNext(token);
                desNode = token;
                des = getAddressingCode(getStr(token));
                /*check if operand type is legal for this operation*/
                if (legalSrcOp(src, opcode) == FALSE)
                {
                    errorILegalAddressing(MM->currentLine, getFT(MM->as)->name, getStr(srcNode), "src");
                    MM->errorFlag = TRUE;
                    return;
                }
                if (legalDesOp(des, opcode) == FALSE)
                {
                    errorILegalAddressing(MM->currentLine, getFT(MM->as)->name, getStr(desNode), "des");
                    MM->errorFlag = TRUE;
                    return;
                }
                if (des == 3 && src == 3) /*if both are register combine them to 1 code line*/
                {
                    srcNode = MLgetAddress(srcNode, MM, src, TRUE);
                    tempML = getML(srcNode);
                    tempML->BMC = setValue(tempML->BMC, isRegister(getStr(desNode)));
                    desNode = NULL;
                }
                else
                {
                    srcNode = MLgetAddress(srcNode, MM, src, TRUE);
                    desNode = MLgetAddress(desNode, MM, des, FALSE);
                }
            }
            if (srcNode != NULL) /*add des to src node*/
            {
                TempNode = srcNode;
                while (getNext(TempNode) != NULL)
                {
                    TempNode = getNext(TempNode);
                }
                TempNode->next = desNode;
            }
            if (firstMLline != NULL) /*add src and des to first word*/
            {
                firstMLline->next = srcNode;
                tempML = getML(firstMLline);
                tempML->BMC = setSrc(tempML->BMC, src);
                tempML->BMC = setDes(tempML->BMC, des);
            }
            AddCode(MM, firstMLline);
            MM->ic = MM->ic + 1;
        }
        else
        {
            errorIlegalWordCount(MM->currentLine, getFT(MM->as)->name, "operation");
            MM->errorFlag = TRUE;
            return;
        }
    }
    else
    {
        errorMissingWord(MM->currentLine, getFT(MM->as)->name, "operation code");
        MM->errorFlag = TRUE;
        return;
    }
}
/*@@@ Macro functions @@@*/
Mcro *newMcro(char *name)
{
    Mcro *newMcro = (Mcro *)malloc(sizeof(Mcro));
    if (newMcro == NULL)
    {
        errorCouldNotAllocateMemory();
    }
    else
    {
        addToCollector(newNode(newMcro), McroCollector);
    }

    newMcro->name = (char *)malloc(strlen(name) + 1);
    if (newMcro->name == NULL)
    {
        errorCouldNotAllocateMemory();
    }
    else
    {
        addToCollector(newNode(newMcro->name), StringCollector);
    }
    strcpy(newMcro->name, name);
    newMcro->data = NULL;
    return newMcro;
}
Mcro *mcroExists(char *newMcro, MemoryManager *MM)
{
    char *mcroName;
    Mcro *mcro;
    Node *mcroNode = MM->mcro;
    while (mcroNode != NULL)
    {
        mcro = getMcr(mcroNode);
        mcroName = mcro->name;
        if (strcmp(newMcro, mcroName) == 0)
        {
            {
                return mcro;
            }
        }
        mcroNode = getNext(mcroNode);
    }
    return NULL;
}
void advanceData(MemoryManager *MM)
{
    Node *data = MM->data;
    MemoryLine *ml;
    Symbol *symbol;
    while (data != NULL) /*advance address of data lines*/
    {
        ml = getML(data);
        ml->DA = ml->DA + MM->ic + STARTING_ADDRESS;
        data = getNext(data);
    }
    data = MM->symbol;
    while (data != NULL) /*advance address of symbols of data lines*/
    {
        symbol = getSymbol(data);
        if (symbol->property == DATA || symbol->property == STRING)
        {
            symbol->value = symbol->value + MM->ic + STARTING_ADDRESS + 1;
        }
        data = getNext(data);
    }
}

/*@@@ Linked list functions @@@*/
LinkedList *newLinkedList()
{
    LinkedList *newLinkedList = (LinkedList *)malloc(sizeof(LinkedList));
    if (newLinkedList == NULL)
    {
        errorCouldNotAllocateMemory();
    }
    else
    {
        addToCollector(newNode(newLinkedList), LLCollector);
    }
    newLinkedList->head = NULL;
    newLinkedList->size = 0;
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
        while (getNext(current) != NULL) /*get to last node*/
        {
            current = getNext(current);
        }
        current->next = newNode;
    }
    list->size++; /*increase size*/
}

/*@@@ Memory Manager @@@*/
MemoryManager *newMemoryManager(char *name)
{
    MemoryManager *newMemoryManager = (MemoryManager *)malloc(sizeof(MemoryManager));
    if (newMemoryManager == NULL)
    {
        errorCouldNotAllocateMemory();
    }
    newMemoryManager->code = NULL;
    newMemoryManager->data = NULL;
    newMemoryManager->mcro = NULL;
    newMemoryManager->symbol = NULL;
    newMemoryManager->ic = 0;
    newMemoryManager->dc = -1;
    newMemoryManager->currentLine = 0;
    newMemoryManager->errorFlag = FALSE;
    intializeFiles(newMemoryManager, name);
    return newMemoryManager;
}
void AddData(MemoryManager *mm, Node *newData)
{
    Node *currentData = mm->data;
    if (currentData == NULL)
    {
        mm->data = newData;
    }
    else
    {
        while (getNext(currentData) != NULL)
        {
            currentData = getNext(currentData);
        }
        currentData->next = newData;
    }
}
void AddCode(MemoryManager *mm, Node *newCode)
{
    Node *currentCode;
    currentCode = mm->code;
    if (currentCode == NULL)
    {
        mm->code = newCode;
    }
    else
    {
        while (getNext(currentCode) != NULL)
        {
            currentCode = getNext(currentCode);
        }
        currentCode->next = newCode;
    }
}
void AddMcro(MemoryManager *mm, Node *newMcro)
{
    Node *currentMcro;
    currentMcro = mm->mcro;
    if (currentMcro == NULL)
    {
        mm->mcro = newMcro;
    }
    else
    {
        while (getNext(currentMcro) != NULL)
        {
            currentMcro = getNext(currentMcro);
        }
        currentMcro->next = newMcro;
    }
}
void AddSymbol(MemoryManager *mm, Node *newSymbol)
{
    Node *currentSymbol;
    currentSymbol = mm->symbol;
    if (currentSymbol == NULL)
    {
        mm->symbol = newSymbol;
    }
    else
    {
        while (getNext(currentSymbol) != NULL)
        {
            currentSymbol = getNext(currentSymbol);
        }
        currentSymbol->next = newSymbol;
    }
}
int getRegisterValue(char *token)
{
    int value;
    if (token[0] == 'r' && isdigit(token[1]) && token[2] == '\0')
    {
        value = token[1];
        value = value - 48; /*48 is int value of character 0*/
        if (0 <= value && value <= 7)
        {
            return value;
        }
        else
        {
            return UNDEFINED;
        }
    }
    else
    {
        return UNDEFINED;
    }
}
int getImidiateValue(char *token, MemoryManager *MM)
{
    Symbol *symbol;
    int success = FALSE, value;
    char *symbolPointer = token;
    symbolPointer++;
    value = stringToInt(symbolPointer, &success);
    if (success == TRUE)
    {
        if (legalInteger(value) == FALSE)
        {
            errorIlegalInteger(MM->currentLine, getFT(MM->as)->name, symbolPointer);
            MM->errorFlag = TRUE;
            return UNDEFINED;
        }
        return value;
    }
    else
    {
        symbol = symbolExists(symbolPointer, MM);
        if (symbol == NULL)
        {
            errorMissingDecleration(MM->currentLine, getFT(MM->as)->name, symbolPointer);
            MM->errorFlag = TRUE;
            return UNDEFINED;
        }
        else
        {
            if (symbol->property != MDEFINE)
            {
                errorIlegalWordPlace(MM->currentLine, getFT(MM->as)->name, "#", token, symbolPointer, "defined value or +/-[digit][digit]...");
                MM->errorFlag = TRUE;
                return UNDEFINED;
            }
            else
            {
                return symbol->value;
            }
        }
    }
}
void printAll(MemoryManager *MM)
{
    Node *code = MM->code;
    Node *SC = NULL;
    printf("printing Code+Data:\n");
    while (code != NULL)
    {
        printf("address:%d ,sourceCode:%s binaryCode:", getML(code)->DA, getStr(getML(code)->SC));
        if (getML(code)->BMC == UNDEFINED)
        {
            printf("?\n");
        }
        else
        {
            printBinary(getML(code)->BMC);
        }
        code = getNext(code);
    }
    code = MM->data;
    while (code != NULL)
    {
        SC = getML(code)->SC;
        if (SC != NULL)
        {
            printf("address:%d ,sourceCode:%s binaryCode:", getML(code)->DA, getStr(getML(code)->SC));
        }
        else
        {
            printf("address:%d ,sourceCode:%s binaryCode:", getML(code)->DA, "null");
        }
        if (getML(code)->BMC == UNDEFINED)
        {
            printf("?\n");
        }
        else
        {
            printBinary(getML(code)->BMC);
        }
        code = getNext(code);
    }
    printf("\nsymbolTable\n");
    code = MM->symbol;
    while (code != NULL)
    {
        printf("symbol:%s ,type:%d value:%d\n", getSymbol(code)->name, getSymbol(code)->property, getSymbol(code)->value);
        code = getNext(code);
    }
}
/*@@@ File Tracker @@@*/
FileTracker *newFileTracker(char *name)
{
    FileTracker *newFile = (FileTracker *)malloc(sizeof(FileTracker));
    if (newFile == NULL)
    {
        errorCouldNotAllocateMemory();
    }
    else
    {
        addToCollector(newNode(newFile), FileTrackerCollector);
    }
    newFile->name = (char *)malloc(strlen(name) + 1);
    if (newFile->name == NULL)
    {
        errorCouldNotAllocateMemory();
    }
    else
    {
        addToCollector(newNode(newFile->name), StringCollector);
    }
    strcpy(newFile->name, name);
    newFile->file = NULL;
    newFile->state = FALSE;
    return newFile;
}
FILE *openFile(FileTracker *fileTracker, char *type)
{
    FILE *openFile;
    /*reason for closing and reopening is incase file is open on write but i want to open it on read, type adjusts how to open it for read or write*/
    if (fileTracker->state == TRUE) /*check if file is already open,close file and reopen, return pointer to it*/
    {
        fclose(fileTracker->file);
    }
    openFile = fopen(fileTracker->name, type);
    if (openFile == NULL)
    {
        errorCouldNotOpenFile(fileTracker->name);
    }

    fileTracker->state = TRUE;
    fileTracker->file = openFile;
    return fileTracker->file;
}
void CloseFile(FileTracker *fileTracker)
{
    if (fileTracker->state == TRUE)
    {
        fclose(fileTracker->file);
        fileTracker->state = FALSE;
    }
}
void intializeFiles(MemoryManager *mm, char *name)
{
    char *ending;
    FileTracker *File;
    ending = addFileEnding(name, AS);
    File = newFileTracker(ending);
    mm->as = newNode(File);
    ending = addFileEnding(name, AM);
    File = newFileTracker(ending);
    mm->am = newNode(File);
    ending = addFileEnding(name, OB);
    File = newFileTracker(ending);
    mm->ob = newNode(File);
    ending = addFileEnding(name, ENTRY);
    File = newFileTracker(ending);
    mm->ent = newNode(File);
    ending = addFileEnding(name, EXTERN);
    File = newFileTracker(ending);
    mm->ext = newNode(File);
}
/*@@@ Memory Lines @@@*/
MemoryLine *newMemoryLine(int address)
{
    MemoryLine *newML = (MemoryLine *)malloc(sizeof(MemoryLine));
    if (newML == NULL)
    {
        errorCouldNotAllocateMemory();
    }
    else
    {
        addToCollector(newNode(newML), MLCollector);
    }
    newML->DA = address;
    newML->BMC = 0;
    newML->SC = NULL;
    newML->type = 0;
    return newML;
}
Node *MLgetAddress(Node *token, MemoryManager *MM, int addressing, int isSrc)
{
    int value;
    Node *returnedNode, *tempNode;
    MemoryLine *tempML;
    Symbol *tempSymbol;
    /*assign address acording to adressing*/
    if (addressing == 0)
    {
        value = getImidiateValue(getStr(token), MM);
        MM->ic = MM->ic + 1;
        tempML = newMemoryLine(MM->ic + STARTING_ADDRESS);
        tempML->SC = token;
        tempML->BMC = setValue(0, value);
        returnedNode = newNode(tempML);
    }
    if (addressing == 1)
    {
        MM->ic = MM->ic + 1;
        tempML = newMemoryLine(MM->ic + STARTING_ADDRESS);
        tempML->SC = token;
        tempML->BMC = UNDEFINED;
        tempML->type = 0;
        tempSymbol = symbolExists(getStr(token), MM);
        if (tempSymbol != NULL)
        {
            if (tempSymbol->property == EXTERN)
            {
                tempML->BMC = setARE(0, EXTERN);
                tempML->type=EXTERN;
            }
        }
        returnedNode = newNode(tempML);
    }
    if (addressing == 2)
    {
        tempNode = newNode(getArraySymbol(getStr(token)));
        tempSymbol = symbolExists(getStr(tempNode), MM);
        if (tempSymbol == NULL) /*code line for symbol, if not declared yet ,address undefined*/
        {
            MM->ic = MM->ic + 1;
            tempML = newMemoryLine(MM->ic + STARTING_ADDRESS);
            tempML->SC = tempNode;
            tempML->BMC = UNDEFINED;
            returnedNode = newNode(tempML);
        }
        else
        {
            value = tempSymbol->value;
            MM->ic = MM->ic + 1;
            tempML = newMemoryLine(MM->ic + STARTING_ADDRESS);
            tempML->SC = token;
            tempML->BMC = setValue(0, value);
            returnedNode = newNode(tempML);
        }
        /*code line  for adress in array*/
        value = GetArrayData(getStr(token), MM);
        MM->ic = MM->ic + 1;
        tempML = newMemoryLine(MM->ic + STARTING_ADDRESS);
        tempML->SC = newNode(GetArrayDataSymbol(getStr(token), MM));
        tempML->BMC = setValue(0, value);
        returnedNode->next = newNode(tempML);
    }
    if (addressing == 3)
    {
        MM->ic = MM->ic + 1;
        tempML = newMemoryLine(MM->ic + STARTING_ADDRESS);
        tempML->SC = token;
        value = isRegister(getStr(token));
        if (isSrc == FALSE) /*adjuist value if its a src register or des*/
        {
            tempML->BMC = setValue(0, value);
        }
        else
        {
            tempML->BMC = setRegSrc(0, value);
        }
        returnedNode = newNode(tempML);
    }
    return returnedNode;
}
