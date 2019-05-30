#ifndef CONSTANTS_H
#define CONSTANTS_H
#include <linux/types.h>
#include <asm/swab.h>

#define INSTRUCTION_SIZE 4 //in bytes
#define NUMBER_OF_REGISTERS 32
#define BASE_ADDRES 0x80000000

#define REVERSE16(x) ((__u16)( \
	(((__u16)(x) & (__u16)0x00ffU) << 8) | \
	(((__u16)(x) & (__u16)0xff00U) >> 8)))

#define REVERSE32(x) ((__u32)(				\
	(((__u32)(x) & (__u32)0x000000ffUL) << 24) | \
	(((__u32)(x) & (__u32)0x0000ff00UL) <<  8) | \
	(((__u32)(x) & (__u32)0x00ff0000UL) >>  8) | \
	(((__u32)(x) & (__u32)0xff000000UL) >> 24)))

extern char* REGISTER_NAMES[NUMBER_OF_REGISTERS];

enum ERROR_CODES {
	SUCCESS = 1,
	UNSPORTED_INSTRUCTION = 2,
	ALLOCATION_ERROR = 3,
};


#endif

