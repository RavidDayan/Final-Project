CC = gcc
CFLAGS = -Wall -ansi -pedantic -g
LIBS = -lm

all: assembler

assembler: util.c binary.c errors.c dataStructs.c  buildFiles.c parser.c  preProccess.c firstPass.c secondPass.c MemoryCollector.c opcode.c assembler.c
	$(CC) $(CFLAGS) util.c binary.c errors.c dataStructs.c  buildFiles.c parser.c  preProccess.c firstPass.c secondPass.c MemoryCollector.c opcode.c assembler.c -o assembler $(LIBS)