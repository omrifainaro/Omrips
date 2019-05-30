#include "Instruction.h"
//http://www.mrc.uidaho.edu/mrc/people/jff/digital/MIPSir.html all instructions

INST_INFO rFunctionCode[BIGGEST_OPCODE_R] = {
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

INST_INFO ijFunctionCode[BIGGEST_OPCODE_IJ] = {
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

void printInstruction(INSTRUCTION* inst, uint32_t baseAddr) {
	int addr;
	switch(inst->type.rInstruction.opcode){
		case 0:
			printf("%s %s, %s, %s\n", rFunctionCode[inst->type.rInstruction.func].name, REGISTER_NAMES[inst->type.rInstruction.rs], REGISTER_NAMES[inst->type.rInstruction.rd], 
			REGISTER_NAMES[inst->type.rInstruction.rt]);
			break;
		case 2:
		case 3:
			addr = inst->type.jInstruction.addr;
			addr = addr << 2;
			addr = (baseAddr & ~0xfffffff) ^ addr;
			printf("%s 0x%x\n", ijFunctionCode[inst->type.jInstruction.opcode].name, addr);
			break;
		default:
			printf("%s %s, %s, 0x%x\n", ijFunctionCode[inst->type.iInstruction.opcode].name, REGISTER_NAMES[inst->type.iInstruction.rt],
			REGISTER_NAMES[inst->type.iInstruction.rt], inst->type.iInstruction.imm);			
		
	}
}