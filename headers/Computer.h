#ifndef COMPUTER_H
#define COMPUTER_H

#include "Cpu.h"
#include "Ram.h"

void run(void* va, void* code, uint32_t size);

#endif