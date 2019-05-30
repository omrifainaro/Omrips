#include "Instruction.h"
//http://www.mrc.uidaho.edu/mrc/people/jff/digital/MIPSir.html all instructions

int BASE_ADDRESS = 0x0;

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
			printf("%s %s, %s, 0x%x\n", ijFunctionCode[inst->type.iInstruction.opcode].name, REGISTER_NAMES[inst->type.iInstruction.rt],
			REGISTER_NAMES[inst->type.iInstruction.rt], inst->type.iInstruction.imm);			
		
	}
}

void setPc(unsigned int pc) { 
	BASE_ADDRESS = pc; 
}
