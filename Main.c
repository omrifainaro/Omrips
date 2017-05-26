#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Instruction.h"
#include "Utils.h"

extern void reverseString(char*, int);
void pause();

int main() {
	FILE* f = fopen("helloworld", "r+b");
	INSTRUCTION* inst;
	unsigned char* opcode = (unsigned char*)malloc(INSTRUCTION_SIZE);
	unsigned int entrypoint = 0x0;
	if (f == NULL || ferror(f)) {
		perror("Error opening file...\n");
		return -1;
	}
	fseek(f, 0x18, SEEK_SET);
	printf("file: %p, 0x%x\n", f, entrypoint);
	fread(&entrypoint, sizeof(unsigned int), 1, f);
	fseek(f, entrypoint,SEEK_SET);
	printf("%06lx", ftell(f));
	int i = 0;
	while (fread(opcode, sizeof(char), INSTRUCTION_SIZE, f) >= INSTRUCTION_SIZE) {
		if (i > 10) break;
		i++;
		reverseString(opcode, INSTRUCTION_SIZE);
		inst = newInstruction(*(unsigned int*)opcode);
		printf("fileoffset: %06lx) ", ftell(f));
		printInstruction(inst);
	}
	printf("1");
	fclose(f);
	printf("2");
	free(inst);
	printf("3");
	free(opcode);
	printf("4");
	pause();
	return 0;
}

void pause() {
	printf("press any key to continue...");
	getchar();
}
