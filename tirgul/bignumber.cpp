#include <list>
#include <vector>
#include <iostream>
#include <algorithm>
#include <tr1/functional>


void PrintNum(int _num)
{
	std::cout << _num;
}

std::list<int> Multiply(const std::list<int>& _first, const std::list<int>& _second)
{
	std::size_t numDigits = _first.size() + _second.size();
	std::vector<int> result(numDigits, 0);
	
	int firstCount = 0, secondCount = 0, carry = 0;
	for(std::list<int>::const_reverse_iterator firstItr = _first.rbegin(); firstItr != _first.rend(); ++firstItr, ++firstCount)
	{
		for(std::list<int>::const_reverse_iterator secondItr = _second.rbegin(); secondItr != _second.rend(); ++secondItr, ++secondCount)
		{
			int digit = firstCount + secondCount;
			
			int sum = (*firstItr) * (*secondItr) + result[digit] + carry;
			
			result[digit] = sum % 10;
			carry = sum / 10;
		}
		
		result[firstCount + secondCount] += carry;
		carry = secondCount = 0;
	}
	
	return std::list<int>(result.rbegin(), result.rend());
}

int main()
{
	
	int firstArray[] = {1,2,5,4,8,7};
	int secondArray[] = {2,6,4,8,7};
	
	std::list<int> first(firstArray, firstArray + sizeof(firstArray)/sizeof(firstArray[0]));
	std::list<int> second(secondArray, secondArray + sizeof(secondArray)/sizeof(secondArray[0]));
	
	std::list<int> result = Multiply(first, second);
	
	std::for_each(result.begin(), result.end(), PrintNum);
	
	std::cout << std::endl;
	
	return 1;
}
