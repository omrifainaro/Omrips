all: Main.c
	gcc Main.c Instruction.c -include Utils.h Constants.h Instruction.h -o omrips
clean:
	$(RM) omrips
