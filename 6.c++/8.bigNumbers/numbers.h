#ifndef __BIG_NUMBER_H__
#define __BIG_NUMBER_H__

#include <string>
#include <iomanip>
#include <locale>
#include <sstream>

using namespace std;

class big_number_t
{
	public:
		big_number_t (){};
		~big_number_t (){};
		big_number_t (const char* _number);
		big_number_t (int _number);
		big_number_t (const big_number_t& _number);
		big_number_t& operator=(const big_number_t& _number);
		big_number_t& operator=(int _number);
		bool operator==(const big_number_t& _number) const;
		bool operator<(const big_number_t& _number) const;
		bool operator>(const big_number_t& _number) const;
		big_number_t operator+(big_number_t& _number)const;
		big_number_t operator-(big_number_t& _number)const;

	private:
		/* data */
		string m_number;
		
	private:
		int AddDigit(int _a, int _b, int* _reserve) const;
		int SubtractDigit(int _a, int _b, int* _reserve) const;
		bool IsLarger(const string& _other) const;
		int  CharToDigit(char _character) const;
		char  DigitToChar(int _digit) const;
		void GetLargerString(const string& _str, string* _larger, string* _smaller)const;
		bool IsLarger(string _other)const;
};

#endif /* __BIG_NUMBER_H__ */

