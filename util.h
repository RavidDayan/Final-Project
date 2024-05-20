#ifndef UTIL_H
#define UTIL_H
#include <ctype.h>
/*true false*/
#define TRUE 1
#define FALSE 0

#define UNDEFINED -99999 /*used to identify "null" integers*/
/*represent to biggest allowed integer in a 12 bit memory*/
#define MIN_INT_SIZE −2048
#define MAX_INT_SIZE 2047;
/*operation identifiers*/
#define MDEFINE 0
#define EXTERN 1
#define ENTRY 2
#define DATA 3
#define STRING 4
#define CODE 5
/*ending identifiers*/
#define AS 3
#define AM 4
#define OB 5

#define STARTING_ADDRESS 100

/*adds to the endinds .as .am .ob .ext .ent to the file name */
char *addFileEnding(char *fileName, int type);
/*turns a string of +/-[digit][digit]... to int*/
int stringToInt(char *number, int *success);
#endif