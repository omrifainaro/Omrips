#ifndef UTILS_H
#define UTILS_H

void reverseString(char* str, int size){
	int i = 0, j = size-1;
	char c = 0;
	for(; i < j; i++, j--){
		c = str[i];
		str[i] = str[j];
		str[j] = c;
	}
}


#endif
