#include "Cpu.h"

R2000_CPU cpu = {0};


static int runRTypeInstruction(INSTRUCTION inst){
	switch(inst.type.rInstruction.func){
		default:
			printf("%s not supported yet\n\n", rFunctionCode[inst.type.rInstruction.func].name);
			return UNSPORTED_INSTRUCTION;
	}
}

static int runITypeInstruction(INSTRUCTION inst){
	switch(inst.type.iInstruction.opcode){
		default:
			printf("%s not supported yet\n\n", ijFunctionCode[inst.type.iInstruction.opcode].name);
			return UNSPORTED_INSTRUCTION;
	}
}

static int runJTypeInstruction(INSTRUCTION inst){
	switch(inst.type.jInstruction.opcode){
		default:
			printf("%s not supported yet\n\n", ijFunctionCode[inst.type.jInstruction.opcode].name);
			return UNSPORTED_INSTRUCTION;		
	}
}

int runInstruction(INSTRUCTION inst){
	printf("%p: ", cpu.pc);
	printInstruction(&inst, (unsigned long) cpu.pc);
	cpu.pc += INSTRUCTION_SIZE;	
	switch(inst.type.rInstruction.opcode){
		case 0:
			return runRTypeInstruction(inst);
		case 2:
		case 3:
			return runJTypeInstruction(inst);
			// addr = inst->type.jInstruction.addr;
			// addr = addr << 2;
			// addr = (BASE_ADDRESS & ~0xfffffff) ^ addr;
			// printf("%s 0x%x\n", ijFunctionCode[inst->type.jInstruction.opcode].name, addr);
			break;
		default:
			return runITypeInstruction(inst);
			// printf("%s %s, %s, 0x%x\n", ijFunctionCode[inst->type.iInstruction.opcode].name, REGISTER_NAMES[inst->type.iInstruction.rt],
			// REGISTER_NAMES[inst->type.iInstruction.rt], inst->type.iInstruction.imm);
	}
	return 1;
}

int setPc(void* pc){
	cpu.pc = pc;
	return SUCCESS;
}