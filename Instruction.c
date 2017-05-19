#include "Instruction.h"
//http://www.mrc.uidaho.edu/mrc/people/jff/digital/MIPSir.html all instructions

INSTRUCTION* newInstruction(unsigned int opcode) {
	INSTRUCTION* inst;
	inst = (INSTRUCTION*)malloc(sizeof(INSTRUCTION));
	unsigned char op = opcode >> 26;
	inst->op.ijop = op;
	format f;
	getIJInstructionName(op, &f);
	inst->type = f;
	if (f == R_FORMAT) {
		inst->body.R.func = opcode & 0x3f;
		inst->body.R.shift = (opcode >> 6) & 0x1f;
		inst->body.R.rs = (opcode >> 11) & 0x1f;
		inst->body.R.rt = (opcode >> 16) & 0x1f;
		inst->body.R.rd = (opcode >> 21) & 0x1f;
	}
	else if (f == I_FORMAT) {
		inst->body.I.imm = (opcode & 0xffff) << 2;
		inst->body.I.rs = (opcode >> 16) & 0x1f;
		inst->body.I.rt = (opcode >> 21) & 0x1f;
	}
	else if (f == J_FORMAT) {
		inst->body.J.addr = (opcode & 0x3ffffff) << 2;
	}
	return inst;
}

void printInstruction(INSTRUCTION* inst) {
	printf("%x: ", BASE_ADDRESS);
	if (inst->type == R_FORMAT) {
		printf("%s %s, %s, %s\n", getRInsructionName(inst), REGISTER_NAMES[inst->body.R.rs],
			REGISTER_NAMES[inst->body.R.rd], REGISTER_NAMES[inst->body.R.rt]);
	}
	else if (inst->type == I_FORMAT) {
		int imm = inst->body.I.imm;
		printf("%s %s, %s, [pc %c %x]\n", getIJInstructionName(inst->op.ijop, &inst->type), REGISTER_NAMES[inst->body.I.rs],
			REGISTER_NAMES[inst->body.I.rt], (imm<0) ? '-' : '+', (imm<0) ? -imm : imm);
	}
	else if (inst->type == J_FORMAT) {
		int addr = inst->body.J.addr;
		printf("%s 0x%x\n", getIJInstructionName(inst->op.ijop, &inst->type), addr);
	}
}

char* getIJInstructionName(unsigned char op, format* f) {
	switch (op)
	{
	case BNE:
		*f = I_FORMAT;
		return "BNE";
	case BEQ:
		*f = I_FORMAT;
		return "BEQ";
	case SB:
		*f = I_FORMAT;
		return "SB";
	case SH:
		*f = I_FORMAT;
		return "SH";
	case SW:
		*f = I_FORMAT;
		return "SW";
	case LB:
		*f = I_FORMAT;
		return "LB";
	case LBU:
		*f = I_FORMAT;
		return "LBU";
	case LH:
		*f = I_FORMAT;
		return "LH";
	case LHU:
		*f = I_FORMAT;
		return "LHU";
	case LW:
		*f = I_FORMAT;
		return "LW";
	case J:
		*f = J_FORMAT;
		return "J";
	case JAL:
		*f = J_FORMAT;
		return "JAL";
		//case JALR:
		//	break;
	case LHI:
		*f = I_FORMAT;
		return "LHI";
	case ORI:
		*f = I_FORMAT;
		return "ORI";
	case ADDI:
		*f = I_FORMAT;
		return "ADDI";
	case ADDIU:
		*f = I_FORMAT;
		return "ADDIU";
	case ANDI:
		*f = I_FORMAT;
		return "ANDI";
	case XORI:
		*f = I_FORMAT;
		return "XORI";
	case SLTI:
		*f = I_FORMAT;
		return "SLTI";
	case MFHI:
		*f = I_FORMAT;
		return "MFHI";
		//case SLTIU:
		//	break;
	case MTHI:
		*f = I_FORMAT;
		return "MTHI";
	default:
		*f = R_FORMAT;
		return "NULL";
	}
}

char* getRInsructionName(INSTRUCTION* inst) {
	switch (inst->body.R.func) {
	case ADD:
		return "ADD";
	case ADDU:
		return "ADDU";
	case AND:
		return "AND";
	case DIV:
		return "DIV";
		break;
	case DIVU:
		return "DIVU";
	case MULT:
		return "MULT";
	case MULTU:
		return "MULTU";
	case NOR:
		return "NOR";
	case OR:
		return "OR";
	case SLL:
		return "SLL";
	case SLLV:
		return "SLV";
	case SRA:
		return "SRA";
	case SRAV:
		return "SRAV";
	case SRL:
		return "SRL";
	case SRLV:
		return "SRLV";
	case SUB:
		return "SUB";
	case SUBU:
		return "SUBU";
	case XOR:
		return "XOR";
		//case LLO:
		//	break;
	case SLT:
		return "SLT";
	case SLTU:
		return "SLTU";
		//case BGTZ: dont know yet what to do
		//	break;   these instructions are real
		//case BLEZ:
		//	break;
	case MFLO:
		return "MFLO";
	case MTLO:
		return "MTLO";
		//case TRAP:
		//	break;
	case JR:
		return "JR";
	default:
		return "NULL";
	}
}