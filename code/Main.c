//32 bits
#include <sys/mman.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <elf.h>
#include <fcntl.h>
#include <unistd.h>

#include "Instruction.h"
#include "Computer.h"

void* loadFile(char* filename){
	int fd;
	struct stat sb;
	void* fileBase;

	fd = open(filename, O_RDONLY);
	if (!fd){
		perror("Error opening file...\n");
		exit(1);
	}

	if (fstat(fd, &sb) == -1){
		perror("Error getting file stats");
		exit(1);
	}

	fileBase = mmap(NULL, sb.st_size, PROT_READ, MAP_PRIVATE, fd, SEEK_SET);
	if (fileBase == MAP_FAILED){
		perror("Error mapping file to memory");
		exit(1);	
	}

	close(fd);
	return fileBase;
}

Elf32_Shdr* getTextSection(Elf32_Ehdr* elfHeader, void* fileBase, unsigned int entrypoint){
	int i = 0;
	void* fPointer;
	Elf32_Shdr* sh;
	fPointer = fileBase + REVERSE32(elfHeader->e_shoff);
	for(; i < REVERSE16(elfHeader->e_shnum); i++){
		fPointer += REVERSE16(elfHeader->e_shentsize);
		sh = (Elf32_Shdr*) fPointer;
		if(entrypoint > REVERSE32(sh->sh_addr) && entrypoint < REVERSE32(sh->sh_addr) + REVERSE32(sh->sh_size)){
			return sh;
		}
	}
	return NULL; //Not found!
}

void dumpAllInstructions(Elf32_Shdr* sh, void* fileBase){
	int i = 0, fOffset = 0;
	void* fPointer = NULL;
	unsigned int opcode;
	INSTRUCTION inst;
	//int numOpcodes = REVERSE32(sh->sh_size) / INSTRUCTION_SIZE;
	int numOpcodes = 20;
	fOffset = REVERSE32(sh->sh_addr) - REVERSE32(sh->sh_offset);
	fPointer = fileBase + REVERSE32(sh->sh_offset);
	setPc((char*)((char*)fPointer - (char*)fileBase + fOffset));

	while(i++ < numOpcodes){
		opcode = REVERSE32(*(unsigned int*) fPointer);
		memcpy(&inst, &opcode, INSTRUCTION_SIZE);
		//printInstruction(&inst);
		runInstruction(inst);
		fPointer += INSTRUCTION_SIZE;
	}
}

void printDebuggingData(unsigned int entrypoint, Elf32_Ehdr* elfHeader){
	printf("Entrypoint: 0x%x\n", entrypoint);
	printf("Section header offset: 0x%x\n", REVERSE32(elfHeader->e_shoff));
	printf("Section header size: 0x%x\n", REVERSE16(elfHeader->e_shentsize));
	printf("Number of entries in the section: 0x%x\n", REVERSE16(elfHeader->e_shnum));
	printf("Size of each entry: 0x%x\n\n", REVERSE16(elfHeader->e_shentsize));
}

int main(int argc, char* argv[]) {
	unsigned int entrypoint;
	char* fileBase;
	Elf32_Ehdr* elfHeader;
	Elf32_Shdr* textSection;
	
	if (argc != 2) {
		printf("Usage: %s <filename>\n", argv[0]);
		return -1;
	}

	/////////Open file and load it to memory//////////
	fileBase = (char*) loadFile(argv[1]);

	/////////File to elf structs///////////	
	elfHeader = (Elf32_Ehdr*) fileBase;
	entrypoint = REVERSE32(elfHeader->e_entry);

	/////////Print nessecary data for debugging//////////////
	printDebuggingData(entrypoint, elfHeader);
	
	//find text section
	textSection = getTextSection(elfHeader, fileBase, entrypoint);

	//Load and run the code
	void* va = (void *)(unsigned long)REVERSE32(textSection->sh_addr);
	void* code = fileBase + REVERSE32(textSection->sh_offset);
	uint32_t size = REVERSE32(textSection->sh_size);
	run(va, code, size);
	
	///////////////////Read all instructions////////////////
	//dumpAllInstructions(textSection, fileBase);
	return 0;
}
