#include "Instruction.h"
//http://www.mrc.uidaho.edu/mrc/people/jff/digital/MIPSir.html all instructions

INSTRUCTION* newInstruction(unsigned int opcode) {
	INSTRUCTION* inst;
	inst = (INSTRUCTION*)malloc(sizeof(INSTRUCTION));
	memcpy(inst, &opcode, INSTRUCTION_SIZE);
	return inst;
}

void printInstruction(INSTRUCTION* inst) {
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
			addr = (BASE_ADDRESS & ~0xfffffff) ^ addr;
			printf("%s 0x%x\n", ijFunctionCode[inst->type.jInstruction.opcode].name, addr);
			break;
		default:
			printf("%s %s, %s, %d\n", ijFunctionCode[inst->type.iInstruction.opcode].name, REGISTER_NAMES[inst->type.iInstruction.rt],
			REGISTER_NAMES[inst->type.iInstruction.rt], inst->type.iInstruction.imm);			
		
	}
}
