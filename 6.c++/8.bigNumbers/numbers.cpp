#include <iostream>
#include <algorithm>
#include <string>

#include "numbers.h"

using namespace std;

big_number_t::big_number_t(const char* _number): m_number(_number){}

big_number_t::big_number_t(int _number): 
		m_number(static_cast<ostringstream*>( &(ostringstream() << _number) )->str()){}

big_number_t& big_number_t::operator=(const big_number_t& _number)
{
	m_number = _number.m_number;
}

big_number_t& big_number_t::operator=(int _number)
{
	m_number = static_cast<ostringstream*>( &(ostringstream() << _number) )->str();
}

bool big_number_t::operator==(const big_number_t& _number) const
{
	return (0 == m_number.compare(_number.m_number));
}

bool big_number_t::operator<(const big_number_t& _number) const
{
	return !IsLarger(_number.m_number);
}

bool big_number_t::operator>(const big_number_t& _number) const
{
	return IsLarger(_number.m_number);
}

int  big_number_t::CharToDigit(char _character) const
{
	return _character - '0';
}

char  big_number_t::DigitToChar(int _digit) const
{
	return _digit + '0';
}

int big_number_t::AddDigit(int _a, int _b, int* _reserve) const
{
	int result = _a + _b + *_reserve;
	*_reserve = result / 10;
	return result % 10;
}

int big_number_t::SubtractDigit(int _a, int _b, int* _reserve) const
{
	int result = _a - _b - *_reserve;
	if(result > 0)
	{
		*_reserve = 0;
		return result;
	}
	
	*_reserve = 1;
	return result * (-1);
}

void big_number_t::GetLargerString(string& _str, string* _larger, string* _smaller)
{	
	if(IsLarger(_str))
	{
		_larger = &(this->m_number);
		_smaller = &_str;
	}
	else
	{
		_larger = &_str;
		_smaller = &(this->m_number);
	}
}

bool big_number_t::IsLarger(const string& _other) const
{
	unsigned mySize = m_number.size();
	unsigned otherSize = _other.size();
	
	if(mySize == otherSize)
	{
		return (m_number.compare(_other) > 0);
	}
	else
	{
		return (mySize > otherSize);
	}
}

big_number_t big_number_t::operator+(big_number_t& _number)
{
	string newString;
	string *larger, *smaller;
	int reserve = 0;
	
	GetLargerString(_number.m_number, larger, smaller);
	
	int j = larger->size();
	for(int i = smaller->size(); i >= 0 ; --i, --j)
	{
		newString += DigitToChar(AddDigit(CharToDigit(larger->at(j)), CharToDigit(smaller->at(i)), &reserve));
	}
	
	for(j; j >= 0; --j)
	{
		newString += DigitToChar(AddDigit(0, CharToDigit(larger->at(j)), &reserve));
	}
	
	if(reserve > 0)
	{
		newString += DigitToChar(reserve);
	}
	
	std::reverse(newString.begin(), newString.end());
	
	return big_number_t(newString.c_str());
}


big_number_t big_number_t::operator-(big_number_t& _number)
{
	string newString;
	string *larger, *smaller;
	int reserve = 0;
	
	GetLargerString(_number.m_number, larger, smaller);
	
	int j = larger->size();
	for(int i = smaller->size(); i >= 0 ; --i, --j)
	{
		newString += DigitToChar(SubtractDigit(CharToDigit(larger->at(j)), CharToDigit(smaller->at(i)), &reserve));
	}
	
	for(j; j >= 0; --j)
	{
		newString += DigitToChar(SubtractDigit(0, CharToDigit(larger->at(j)), &reserve));
	}
	
	if(reserve > 0)
	{
		newString += DigitToChar(reserve);
	}
	
	if(!IsLarger(_number.m_number))
	{
		newString += '-';
	}
	
	std::reverse(newString.begin(), newString.end());
	
	return big_number_t(newString.c_str());
}

