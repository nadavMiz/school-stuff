#include "recursion2.h"

char string[4] = "1234";
double result;
int main()
{
	printTriangle(18);
	printReverseTriangle(18);
	multypecationTable(1, 1, 10);
	printPermutations(string, 3, 0);
	
	return 1;
}
