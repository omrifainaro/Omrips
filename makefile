OBJECTS = code/Main.c code/Instruction.c code/Constants.c code/Utils.c
HEADER_PATH = headers/
all: ${OBJECTS}
	gcc ${OBJECTS} -I ${HEADER_PATH} -o mipsEmulator

run: mipsEmulator examples/hello
	./mipsEmulator examples/hello
	
clean:
	$(RM) omrips
