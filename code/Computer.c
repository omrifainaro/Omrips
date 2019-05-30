#include "Computer.h"

void run(void* va, void* code, uint32_t size) {
	int iRet = allocateMemoryForCode(va, code, size);
	unsigned int opcode;
	INSTRUCTION inst;
	setPc((void *) procCode.virtualMemory);

	for (int i = 0; i < size/INSTRUCTION_SIZE; ++i) {
		opcode = REVERSE32(*(unsigned int*) getVirtualMemory(procCode, cpu.pc));
		memcpy(&inst, &opcode, INSTRUCTION_SIZE);
		runInstruction(inst);
	}
}