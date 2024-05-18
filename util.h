#include <ctype.h>
#define TRUE 1
#define FALSE 0

#define UNDEFINED -99999
#define MIN_INT_SIZE −2048
#define MAX_INT_SIZE 2047;
#define MDEFINE 0
#define MDEFINE_SIZE 4
#define EXTERN 1
#define ENTRY 2
#define DATA 3
#define STRING 4
#define CODE 5

#define AS 3
#define AM 4
#define OB 5
#define DECIMAL 10
#define STARTING_ADDRESS 100

char *addFileEnding(char *fileName, int type);
int stringToInt(char *number, int *success);