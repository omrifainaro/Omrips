#include "Ram.h"

SEGMENT procCode = {0};

int allocateMemoryForCode(void* virtualMemory, void* code, uint32_t size) {
	procCode.addr = malloc(size);
	if (!procCode.addr) {
		return ALLOCATION_ERROR;
	}
	procCode.virtualMemory = (unsigned long) virtualMemory;
	memcpy(procCode.addr, code, size);
	return SUCCESS;
}