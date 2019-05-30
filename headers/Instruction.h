#ifndef INSTRUCTION_H
#define INSTRUCTION_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include "Constants.h"

#define BIGGEST_OPCODE_R 43
#define BIGGEST_OPCODE_IJ 44

typedef struct {
	unsigned int func:6;
	unsigned int shift:5;
	unsigned int rd:5;
	unsigned int rt:5;
	unsigned int rs:5;
	unsigned int opcode:6;
} R_INSTRUCTION;

typedef struct {
	signed int imm:16;
	unsigned int rt:5;
	unsigned int rs:5;
	unsigned int opcode:6;
} I_INSTRUCTION;

typedef struct {
	unsigned int addr:26;
	unsigned int opcode:6;
} J_INSTRUCTION;

typedef	struct {
	union {
	R_INSTRUCTION rInstruction;
	I_INSTRUCTION iInstruction;
	J_INSTRUCTION jInstruction;
	} type;
} INSTRUCTION;

typedef struct{
	int code;
	char name[8];
}INST_INFO;

extern INST_INFO rFunctionCode[BIGGEST_OPCODE_R];
extern INST_INFO ijFunctionCode[BIGGEST_OPCODE_IJ];

void printInstruction(INSTRUCTION* inst, uint32_t baseAddr);

#endif
