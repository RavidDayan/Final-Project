
#ifndef DATASTRUCTS_H
#define DATASTRUCTS_H

#define MDEFINE 0
#define CODE 1
#define DATA 2
#define MACRO 1
#define MEMORY 2
#define LABEL 3
#define TOKEN 4

typedef struct Mcro
{
    char *name;
    char *data;
} Mcro;

typedef struct label
{
    char *name;
    int property;
    int address;
} label;
typedef struct token
{
    char *token;
} token;

Mcro *newMcro(char *name);


#endif