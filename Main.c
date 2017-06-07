//32 bits

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <elf.h>
#include "Instruction.h"
#include "Utils.h"

extern void reverseString(char*, int);
void pause();

void printBytes(unsigned char* tootim, int size){
	int i = 0;
	unsigned char cur = 0;
	printf("opcode: ");
	for(; i < size; i++){
		cur = *(tootim+i);
		if(cur >= 0 && cur <= 9)
			printf("0");
		printf("%x", cur);
	}
	printf("\t");
}

int main() {
	long fsize;	
	FILE* f;
	INSTRUCTION* inst;
	unsigned int opcode;
	unsigned int entrypoint;
	char* fileContent;
	Elf32_Ehdr* elfHeader;
	Elf32_Shdr* textSection;
	void* fPointer;
	int numOpcodes;

	int fOffset = 0;
	
	/////////Open file and load it to memory//////////
	f = fopen("hello", "r+b");
	if (f == NULL || ferror(f)) {
		perror("Error opening file...\n");
		return -1;
	}
	
	fseek(f, 0, SEEK_END);
	fsize = ftell(f);
	fseek(f, 0, SEEK_SET);
	
	fileContent = (char*) malloc(fsize + 1);
	fileContent = malloc(fsize + 1);	

	fread(fileContent, fsize, 1, f);
	fclose(f);
	fileContent[fsize] = 0;

	/////////File to elf structs///////////	
	elfHeader = (Elf32_Ehdr*) fileContent;
	entrypoint = reverse32(elfHeader->e_entry);
	//reverseString((char*)&entrypoint, INSTRUCTION_SIZE);

	/////////Print nessecary data for debugging//////////////
	printf("Entrypoint: 0x%x\n", entrypoint);
	printf("Section header offset: 0x%x\n", reverse32(elfHeader->e_shoff));
	printf("Section header size: 0x%x\n", reverse16(elfHeader->e_shentsize));
	printf("Number of entries in the section: 0x%x\n", reverse16(elfHeader->e_shnum));
	printf("Size of each entry: 0x%x\n", reverse16(elfHeader->e_shentsize));
	
	//////////////////print all names of headers//////////////
	//print offsets
	int i = 0;
	Elf32_Shdr* sh;
	fPointer = fileContent + reverse32(elfHeader->e_shoff);
	for(; i < reverse16(elfHeader->e_shnum); i++){
		fPointer += reverse16(elfHeader->e_shentsize);
		sh = (Elf32_Shdr*) fPointer;
		if(entrypoint > reverse32(sh->sh_addr) && entrypoint < reverse32(sh->sh_addr) + reverse32(sh->sh_size)){
			textSection = sh;
			break; //text section found
		}
	}
	
	///////////////////Read first 25 instructions////////////////
	i = 0;
	numOpcodes = reverse32(sh->sh_size) / INSTRUCTION_SIZE;
	fOffset = reverse32(sh->sh_addr); - reverse32(sh->sh_offset);
	fPointer = fileContent + reverse32(sh->sh_offset);
	while(i < numOpcodes){
		i++;
		printf("\n");
		printf("0x%lx: ", ((char*)fPointer - (char*)fileContent + fOffset));
		setPc((int)((char*)fPointer - (char*)fileContent + fOffset));
		printBytes(fPointer, INSTRUCTION_SIZE);
		memcpy(&opcode, fPointer, INSTRUCTION_SIZE);
		opcode = reverse32(opcode);
		inst = newInstruction(opcode);
		printInstruction(inst);
		fPointer += INSTRUCTION_SIZE;
	}
	
	free(inst);
	free(f);
	return 0;
}

void pause() {
	printf("press any key to continue...");
	getchar();
}
