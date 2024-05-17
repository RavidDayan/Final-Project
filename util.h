#include <ctype.h>
#define TRUE 1
#define FALSE 0
#define UNDEFINED -99999
#define MDEFINE 0
#define MDEFINE_SIZE 4
#define DATA 1
#define STRING 2
#define EXTERN 3
#define ENTRY 4
#define CODE 5
#define AS 0
#define AM 1
#define ENT 2
#define EXT 3
#define OB 4
#define DECIMAL 10
#define STARTING_ADDRESS 100

char *addFileEnding(char *fileName, int type);
int stringToInt(char *number, int *success);