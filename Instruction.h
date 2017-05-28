#ifndef INSTRUCTION_H
#define INSTRUCTION_H
#include <stdio.h>
#include <stdlib.h>
#include "Constants.h"

static int BASE_ADDRESS = 0x80000000;

typedef enum {
	J = 0x2,
	JAL = 0x3,
	BEQ = 0x4,
	BNE = 0x5,
	ADDI = 0x8,
	ADDIU = 0x9, //check why its the same opcode...
	SLTIU = 0x9,
	SLTI = 0xa,
	ANDI = 0xc,
	ORI = 0xd,
	XORI = 0xe,
	MFHI = 0x10,
	MTHI = 0x11,
	LHI = 0x19,
	LB = 0x20,
	LH = 0x21,
	LW = 0x23,
	LBU = 0x24,
	LHU = 0x25,
	SB = 0x28,
	SH = 0x29,
	SW = 0x2b,
} ij_operator;

typedef enum {
	SLL = 0x0,
	SRL = 0x2,
	SRA = 0x3,
	SLLV = 0x4,
	SRLV = 0x6,
	BLEZ = 0x6, //duplicate
	BGTZ = 0x7,
	SRAV = 0x7, //duplicate
	JR = 0x8,
	MFLO = 0x12,
	MTLO = 0x13,
	MULT = 0x18,
	LLO = 0x18, //duplicate
	MULTU = 0x19,
	DIV = 0x1a,
	TRAP = 0x1a, //duplicate
	DIVU = 0x1b,
	ADD = 0x20,
	ADDU = 0x21,
	SUB = 0x22,
	SUBU = 0x23,
	AND = 0x24,
	OR = 0x25,
	XOR = 0x26,
	NOR = 0x27,
	SLTU = 0x29,
	SLT = 0x2a,
}r_operator;

typedef enum {
	J_FORMAT, I_FORMAT, R_FORMAT
} format;

typedef struct {
	format type;
	union {
		r_operator rop;
		ij_operator ijop;
	} op;
	union {
		struct {
			unsigned char rs;
			unsigned char rt;
			unsigned char rd;
			unsigned char shift;
			unsigned char func;
		} R;
		struct {
			unsigned char rs;
			unsigned char rt;
			unsigned char imm;
		} I;
		struct {
			unsigned int addr;
		} J;
	} body;
} INSTRUCTION;

INSTRUCTION* newInstruction(unsigned int opcode);
void printInstruction(INSTRUCTION* inst);
char* getIJInstructionName(unsigned char op, format* f);
char* getRInsructionName(INSTRUCTION* inst);
static void advancePC() { BASE_ADDRESS += 0x8; }

#endif=
