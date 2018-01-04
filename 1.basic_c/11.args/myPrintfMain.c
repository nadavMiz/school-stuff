#include "myPrintf.h"

int main()
{
	char string1[70] = "my name is %s i am %d years old and i am %f meters tall\n";
	char string2[30] = "i am 30%% sure i'm right \n";
	char string3[30] = "this is an %g invalid string\n";
	myPrintf(string1, "alon", 15, 1.56);
	myPrintf(string2);
	myPrintf(string3, 14);
	return 1;
}
