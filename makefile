CC = gcc
CFLAGS = -Wall -ansi -pedantic -g
LIBS = -lm

all: assembler

assembler: src/util.c src/binary.c src/errors.c src/dataStructs.c  src/buildFiles.c src/parser.c  src/preProccess.c src/firstPass.c src/secondPass.c src/MemoryCollector.c src/opcode.c src/assembler.c
	$(CC) $(CFLAGS) src/util.c src/binary.c src/errors.c src/dataStructs.c  src/buildFiles.c src/parser.c  src/preProccess.c src/firstPass.c src/secondPass.c src/MemoryCollector.c src/opcode.c src/assembler.c -o assembler $(LIBS)