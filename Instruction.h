#ifndef INSTRUCTION_H
#define INSTRUCTION_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Constants.h"

#define BIGGEST_OPCODE_R 43
#define BIGGEST_OPCODE_IJ 44

static int BASE_ADDRESS = 0x0;

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

static INST_INFO rFunctionCode[BIGGEST_OPCODE_R] = {
	{0x0, "SLL"},
	{0x1, ""},
	{0x2, "SRL"},
	{0x3, "SRA"},
	{0x4, "SLLV"},
	{0x5, ""},
	{0x6, "SRLV"},
	{0x7, "SRAV"},
	{0x8, "JR"},
	{0x9, "JALR"},
	{0xa, ""},
	{0xb, "SYSCALL"},
	{0xc, ""},
	{0xd, ""},
	{0xe, ""},
	{0xf, ""},
	{0x10, "MFHI"},
	{0x11, "MTHI"},
	{0x12, "MFLO"},
	{0x13, "MTLO"},
	{0x14, ""},
	{0x15, ""},
	{0x16, ""},
	{0x17, ""},
	{0x18, "MULT"},
	{0x19, "MULTU"},
	{0x1a, "DIV"},
	{0x1b, "DIVU"},
	{0x1c, ""},
	{0x1d, ""},
	{0x1e, ""},
	{0x1f, ""},
	{0x20, "ADD"},
	{0x21, "ADDU"},
	{0x22, "SUB" },
	{0x23, "SUBU"},
	{0x24, "AND"},
	{0x25, "OR"},
	{0x26, "XOR"},
	{0x27, "NOR"},
	{0x28, ""},
	{0x29, "SLTU"},
	{0x2a, "SLT"}
};

static INST_INFO ijFunctionCode[BIGGEST_OPCODE_IJ] = {
	{0x0, ""},
	{0x1, ""},
	{0x2, "J"},
	{0x3, "JAL"},
	{0x4, "BEQ"},
	{0x5, "BNE"},
	{0x6, "BLEZ"},
	{0x7, "BGTZ"},
	{0x8, "ADDI"},
	{0x9, "ADDIU"},
	{0xa, "SLTI"},
	{0xb, "SLTIU"},
	{0xc, "ANDI"},
	{0xd, "ORI"},
	{0xe, "XORI"},
	{0xf, "LUI"},
	{0x10, ""},
	{0x11, ""},
	{0x12, ""},
	{0x13, ""},
	{0x14, ""},
	{0x15, ""},
	{0x16, ""},
	{0x17, ""},
	{0x18, ""},
	{0x19, ""},
	{0x1a, ""},
	{0x1b, ""},
	{0x1c, ""},
	{0x1d, ""},
	{0x1e, ""},
	{0x1f, ""},
	{0x20, "LB"},
	{0x21, "LH"},
	{0x22, "" },
	{0x23, "LW"},
	{0x24, "LBU"},
	{0x25, "LHU"},
	{0x26, ""},
	{0x27, ""},
	{0x28, "SB"},
	{0x29, "SH"},
	{0x2a, ""},
	{0x2b, "SW"}
};

INSTRUCTION* newInstruction(unsigned int opcode);
void printInstruction(INSTRUCTION* inst);
static void setPc(int pc) { BASE_ADDRESS = pc; }

#endif
