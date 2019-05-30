#ifndef CPU_H
#define CPU_H
#include <stdint.h>
#include "Constants.h"
#include "Instruction.h"

typedef struct _R2000_CPU {
	void* pc;
	uint32_t registers[NUMBER_OF_REGISTERS];
} R2000_CPU;

extern R2000_CPU cpu;

int runInstruction(INSTRUCTION inst);
int setPc(void* pc);

#endif