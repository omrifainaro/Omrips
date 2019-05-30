all: Main.c
	gcc Main.c Instruction.c Constants.c Utils.h
clean:
	$(RM) omrips
