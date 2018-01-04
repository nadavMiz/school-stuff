#include <stdio.h>
#include <string.h>
#include "fibonachi.h"

void testFibonachi()
{	
	int i;
	for(i = 0; i < 10; ++i)
	{
		printf("%d ", Fib(i));
	}
	printf("\n");
}

void testFactorial()
{
	int i;
	for(i = 0; i < 10; ++i)
	{
		printf("%d ", Factorial(i));
	}
	printf("\n");
}

void testFibonachiRecursive()
{	
	int i;
	for(i = 0; i < 10; ++i)
	{
		printf("%d ", FibRecursive(i));
	}
	printf("\n");
}

void testPalindrome()
{
	int result;
	char string1[10] = "abcddcba";
	char string2[10] = "12321";
	char string3[10] = "";
	char string4[10] = "123521";
	char string5[10] = "1234351";
	result = palindromeRecursive(string1, strlen(string1));
	printf("%s is %d a palindrome\n", string1, result);
	result = palindromeRecursive(string2, strlen(string2));
	printf("%s is %d a palindrome\n", string2, result);
	result = palindromeRecursive(string3, strlen(string3));
	printf("%s is %d a palindrome\n", string3, result);
	result = palindromeRecursive(string4, strlen(string4));
	printf("%s is %d a palindrome\n", string4, result);
	result = palindromeRecursive(string5, strlen(string5));
	printf("%s is %d a palindrome\n", string5, result);
	

}


int main()
{
	printf("\n");
	testFibonachi();
	testFibonachiRecursive();
	testFactorial();
	testPalindrome();
	return 1;
}
