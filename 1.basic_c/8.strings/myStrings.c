#include <string.h>
#include <math.h>
#include <stdio.h>
#include <ctype.h>
#include "myStrings.h"

int reverseString(char* toReverse){
	int end = strlen(toReverse) -1;
	int start = 0;
	char tmp;
	while(start < end){
		tmp = toReverse[start];
		toReverse[start] = toReverse[end];
		toReverse[end] = tmp;
		++start;
		--end;
	}
}

int isPalindrom(char* toReverse){
	int end = strlen(toReverse) -1;
	int start = 0;
	while(start < end){
		if(toReverse[start] != toReverse[end]) return 0;
		++start;
		--end;
	}
	return 1;
}

int myItoa(int value, char *toString){
	if(!toString) return 0;
	char digitDict[10] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
	int nextDigit;
	/*if value is 0 just return "0" */
	if(value == 0){
		toString = "0";
		return 1;
	}
	int strIdx = 0;

	/* get the sign of value */
	if(value < 0){
		value *= -1;
		toString[strIdx] = '-';
		++strIdx;
	}
	/* get number of digits */
	int devider = 1;
	while(value / devider > 9){
		devider *= 10;
	}
	/* get the digits one by one */
	while(value > 0){
		nextDigit = value / devider;
		toString[strIdx] = digitDict[nextDigit];
		++strIdx;
		value -= nextDigit * devider;
		devider /= 10;
	}
	toString[strIdx] = '\0';
	return 1;
}

int myAtoi(char *str){
	char resultStr[strlen(str)];
	int result;
	int intIdx = 0;
	int stringPos = 0;
	char nextChar = 'a';
	while(nextChar != '\0'){
		nextChar = str[stringPos];
		++stringPos;
		if (isdigit(nextChar) || nextChar == '\0'){
			resultStr[intIdx] = nextChar;
			++intIdx;
		}
		else if(isspace(nextChar)) continue;
		else return 0;
	}
	sscanf(resultStr, "%d", &result);
	return result;
}

int myStrcmp(char* str1, char* str2){
	if(!str1 && !str2) return 0;
	if(!str1) return -1;
	if(!str2) return 1;
	int i = 0;
	int charDiff;
	while(1){
		charDiff = str1[i] - str2[i];
		if(charDiff) return charDiff;
		if(str1[i] == '\0' || str2[i] == '\0') break;
		++i;
	}
	return 0;
}

char *myStrcat(char *dest, const char *src){
	if(!dest) return NULL;
	if(!src) return dest;
	int destIdx = strlen(dest);
	int srcIdx = 0;
	while(src[srcIdx] != '\0'){
		dest[destIdx + srcIdx] = src[srcIdx];
		++srcIdx;
	}
	dest[destIdx + srcIdx] = '\0';
	return dest;
}



