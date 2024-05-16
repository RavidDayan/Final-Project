CC = gcc
CFLAGS = -Wall -ansi -pedantic
LIBS = -lm

all: assembler

assembler: util.c binary.c dataStructs.c parser.c  preProccess.c firstPass.c garbageCollector.c opcode.c assembler.c
	$(CC) $(CFLAGS) util.c binary.c dataStructs.c parser.c  preProccess.c firstPass.c garbageCollector.c opcode.c assembler.c -o assembler $(LIBS)