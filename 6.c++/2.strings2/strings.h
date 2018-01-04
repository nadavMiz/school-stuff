#ifndef __string_H__
#define __string_H__

#include <iostream>
#include <stddef.h>

using namespace std;

class String_t
{
	public:
		String_t(const char* _str);
		String_t(const String_t& _str = "");
		~String_t() {delete[] m_string;};
		void SetString(const char* _str);
		size_t Compare(const String_t& _str) const;
		void ConvertToLower();
		void ConvertToUpper();
		void Prepend(const char* _str);
		void Prepend(const String_t& _str) {Prepend(_str.m_string);};
		bool Contains(const String_t& _str) const;
		bool Contains(const char* _str) const;
		String_t& operator=(const String_t& _str);
		String_t& operator=(const char* _str);
		String_t& operator+=(const String_t& _str);
		String_t& operator+=(const char* _str);
		bool operator<(const char* _str) const;
		bool operator<(const String_t& _str) const {return *this < _str.m_string;};
		bool operator>(const char* _str) const;
		bool operator>(const String_t& _str) const {return *this > _str.m_string;};
		bool operator<=(const char* _str) const;
		bool operator<=(const String_t& _str) const{return *this <= _str.m_string;};
		bool operator>=(const char* _str) const;
		bool operator>=(const String_t& _str) const{return *this >= _str.m_string;};
		bool operator==(const char* _str) const;
		bool operator==(const String_t& _str) const{return *this == _str.m_string;};
		bool operator!=(const char* _str) const;
		bool operator!=(const String_t& _str) const{return *this != _str.m_string;};
		char& operator[](size_t _index) const;
		String_t operator()(size_t start, size_t len);
		size_t Length() const 
		{
			return m_length;
		}
		const char* GetString() const 
		{
			return m_string;
		}
		void Print() const {cout << m_string;}
		size_t FirstCharInString(const char _character) const;
		size_t LastCharInString(const char _character) const;
		static const bool GetCaseSens() {return m_caseSens;};
		static void SetCaseSens(const bool _isCaseSens){m_caseSens = _isCaseSens;};
		static size_t GetCurrentCapacity() {return m_defaultCapacity;};
		static void SetCurrentCapacity(const size_t _newCapacity){m_defaultCapacity = _newCapacity;};

	private:
		char* m_string;
		size_t m_length;
		size_t m_capacity;
		
		/* static data */
		static size_t m_defaultCapacity;
		static size_t m_blockSize;
		static bool m_caseSens;
		
		/*private functions*/
		void CreateFromString(const char* _str);
		size_t GetNewCapacity(size_t _length);
		char* RealocateString(size_t _newCapacity);
};

ostream& operator<<(ostream& _os, const String_t& _str);

istream& operator>>(istream& _is, String_t& _str);

#endif /* __string_H__ */

