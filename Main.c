#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Instruction.h"
#include "Utils.h"

void pause();

int main() {
	FILE* f = fopen("main.exe", "rb");
	INSTRUCTION* inst;
	unsigned char* opcode = (unsigned char*)malloc(INSTRUCTION_SIZE);
	if (!f) {
		printf("Error opening file...\n");
		return -1;
	}
	while (fread(opcode, sizeof(char), INSTRUCTION_SIZE, f) >= INSTRUCTION_SIZE) {
		int i = 0;
		//for (; i < INSTRUCTION_SIZE; i++) {
		//	printf("%x\n", opcode[i], opcode[i]);
		//}
		//getStringHexValue(opcode, INSTRUCTION_SIZE);
		//printf("%d\n", htoi(opcode, INSTRUCTION_SIZE));
		inst = newInstruction(asciiHexValue(opcode, INSTRUCTION_SIZE));
		printInstruction(inst);
	}
	fclose(f);

	pause();
	free(inst);
	free(opcode);
	return 0;
}

void pause() {
	printf("press any key to continue...");
	getchar();
}