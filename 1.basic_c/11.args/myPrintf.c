#include <stdarg.h>
#include <string.h>
#include <stdio.h>
#include "myPrintf.h"

#define MAX_DIGITS 300
#define CHAR_LENGTH 1024

int myPrintf(const char* _toPrint, ...)
{
	int i = 0;
	char* token;
	char* nextCharParam;
	char stringCopy[CHAR_LENGTH];
	char resultString[CHAR_LENGTH];
	char paramString[CHAR_LENGTH];
	int nextParmInt;
	float nextParmFloat;
	
	va_list args;
	va_start(args, _toPrint);
	resultString[0] = '\0';
	strcpy(stringCopy, _toPrint);
	token = strchr(stringCopy, '%');
	while(NULL != token)
	{	
		*token = '\0';
		strcat(resultString, &stringCopy[i]);
		switch(token[1])
		{
			case 'd':
				nextParmInt = va_arg(args, int);
				sprintf(paramString, "%d", nextParmInt);
				break;
			case 'f':
				nextParmFloat = va_arg(args, double);
				sprintf(paramString, "%f", nextParmFloat);
				break;
			case 's':
				nextCharParam = va_arg(args, char*);
				strcpy(paramString , nextCharParam);
				break;
			case '%':
				strcpy(paramString , "%");
				break;
			default:
				return 0;
		}
		strcat(resultString, paramString);
		i = token - stringCopy + 2;
		token = strchr(&stringCopy[i], '%');
	}
	strcat(resultString, &stringCopy[i]);
	fputs(resultString, stdout);
	return 1;
}
