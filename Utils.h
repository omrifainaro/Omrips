#ifndef UTILS_H
#define UTILS_H

#include <math.h>
#define NIBBLE 0x0F

//static unsigned int htoi(unsigned char* str, int size) {
//	int i = 0;
//	unsigned int num = 0;
//	for (i = 0; i < size; i++) {
//		if (str[i] >= 'A' && str[i] <= 'F')
//			num += (str[i] - 55) * pow(16, i);
//		if (str[i] >= '0' && str[i] <= '9')
//			num += (str[i] - 48) * pow(16, i);
//	}
//	return num;
//}

//static unsigned long asciiHexValue(unsigned char* str, int size) {
//	int i = 0;
//	unsigned long num = 0;
//	int c = size * 2 - 1; //starts from 16^0
//	while(1){
//		if (i >= size) break;
//		num += (((unsigned int)str[i] & ~NIBBLE) >> 4)*((unsigned int) pow(16, c--));
//		num += ((unsigned int)str[i] & NIBBLE)*((unsigned int) pow(16, c--));
//		i++;
//	}
//	return num;
//}

#endif
