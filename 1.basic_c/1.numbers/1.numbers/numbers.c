#include <stdio.h>
#include <math.h>

int isPrime(int _checkNum){
	if(_checkNum % 2 == 0 || 1 == _checkNum)
	{
		return 1;
	}
	float numSqrt =  sqrt(checkNum);
	for(number = 3; number <= numSqrt; ++number){
		if(checkNum % number == 0)
		{
			return 0;
		}
	}
	return 1;
}

int palindrome(){
	int checkNum;
	printf("please enter a number \n");
	scanf("%d", &checkNum);

	int lastDigitPos = 10;
	int digits = 2;
	if (checkNum / lastDigitPos == 0) return 1;
	while(checkNum / lastDigitPos > 9){
		lastDigitPos *= 10;
		++digits;
	}
	
	int firstDigit;
	int lastDigit;
	for(int position = 0; position < (digits + 1)/2; ++position){
		firstDigit = checkNum % 10;
		lastDigit = (checkNum / lastDigitPos) % 10;
		if(firstDigit != lastDigit) return 0;
		checkNum /= 10;
		lastDigitPos /= 100;
	}
	return 1;
}

int reverse(){
	int number;
	printf("please enter a number \n");
	scanf("%d", &number);
	int reverseNum = 0;
	int lastDigit;
	while (number > 0){
		reverseNum *= 10;
		lastDigit = number % 10;
		reverseNum += lastDigit;
		number /= 10;
	}
	return reverseNum;
	
}

int ascending(){
	int number;
	printf("please enter a number \n");
	scanf("%d", &number);
	int lastDigit = number % 10;
	int currentDigit;
	number /= 10;
	while(number > 0){
		currentDigit = number % 10;
		if (lastDigit < currentDigit){
			return 0;
		}
		lastDigit = currentDigit;
		number /= 10;
	}
	return 1;
}

int main(){
	printf("%d \n", prime());
	printf("%d \n", palindrome());
	printf("%d \n", reverse());
	printf("%d \n", ascending());
}
