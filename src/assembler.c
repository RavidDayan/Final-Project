#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "stdio.h"
#include "../headers/util.h"
#include "../headers/dataStructs.h"
#include "../headers/preProccess.h"
#include "../headers/firstPass.h"
#include "../headers/secondPass.h"
#include "../headers/buildFiles.h"
#include "../headers/MemoryCollector.h"
#include "../headers/opcode.h"

void assemble(char *fileName);
int main(int argc, char *argv[])
{
    int i;
    if (argc == 1)
    {
        fprintf(stderr, "No file name has been enterd");
        exit(EXIT_FAILURE);
    }

    for (i = 1; i < argc; i++)
    {
        assemble(argv[i]);
    }

    return 0;
}
void assemble(char *fileName)
{
    MemoryManager *memoryManager;
    memoryManager = newMemoryManager(fileName);
    memoryStorage=memoryManager;
    preProccess(memoryManager);
    if (memoryManager->errorFlag == TRUE)
    {
        return;
    }
    firstPass(memoryManager);
    if (memoryManager->errorFlag == TRUE)
    {
        return;
    }
    secondPass(memoryManager);
    if (memoryManager->errorFlag == TRUE)
    {
        return;
    }
    buildFiles(memoryManager);
    releaseAllFileMemory();
}
