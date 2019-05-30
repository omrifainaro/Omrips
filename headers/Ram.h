#ifndef RAM_H
#define RAM_H

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "Constants.h"

typedef struct _SEGMENT {
	void* addr;
	unsigned long virtualMemory;
} SEGMENT;

extern SEGMENT procCode;

int allocateMemoryForCode(void* virtualMemory, void* code, uint32_t size);
static inline void* getVirtualMemory(SEGMENT seg, void* va) {return (void*) (va - seg.virtualMemory + (unsigned long)seg.addr);}

#endif