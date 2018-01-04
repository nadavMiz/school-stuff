#ifndef __string_H__
#define __string_H__

#include <iostream>
#include <stddef.h>

using namespace std;

class String_t
{
	public:
		String_t();
		String_t(const char* _str);
		String_t(const String_t& _str);
		~String_t();
		String_t& operator=(const String_t& _str);
		size_t Length() const;
		void SetString(const char* _str);
		const char* GetString() const;
		size_t Compare(const String_t& _str) const;
		void Print() const;
		void ConvertToLower();
		void ConvertToUpper();
		void Prepend(const char* _str);
		void Prepend(const String_t& _str);
		String_t& operator+=(const String_t& _str);
		String_t& operator+=(const char* _str);
		int Contains(const String_t& _str) const;
		int operator<(const String_t& _str) const;
		int operator>(const String_t& _str) const;
		int operator<=(const String_t& _str) const;
		int operator>=(const String_t& _str) const;
		int operator==(const String_t& _str) const;
		int operator!=(const String_t& _str) const;
		int operator<(const char* _str) const;
		int operator>(const char* _str) const;
		int operator<=(const char* _str) const;
		int operator>=(const char* _str) const;
		int operator==(const char* _str) const;
		int operator!=(const char* _str) const;
		char operator[](size_t _index) const;

	private:
		char* m_string;
		size_t m_length;
		
		void NullInitializer();
};

ostream& operator<<(ostream& _os, const String_t& _str);

istream& operator>>(istream& _is, String_t& _str);

#endif /* __string_H__ */

