all: Main.c
	gcc Main.c Instruction.c Constants.h Utils.h
clean:
	$(RM) omrips
