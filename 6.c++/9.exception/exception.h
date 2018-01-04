#ifndef __TEXCEPTION_H__
#define __TEXCEPTION_H__

#include <string>

using namespace std;

template <class T>
class TException_t
{
	public:
		TException_t (T _obj, const char* _msg, const char* file, unsigned int _lineNum);
		~TException_t (){};
		
		const T& GetObject() const;
		const string& GetMsg() const;
		const string& GetFileName() const;
		unsigned int GetLineNum() const;

	private:
		/* data */
		string m_msg;
		string m_fileName;
		unsigned int m_lineNum;
		T m_object;
};

template <class T>
TException_t<T>::TException_t(T _obj, const char* _msg, const char* file, unsigned int _lineNum)
				: m_object(_obj), m_msg(_msg), m_fileName( file)
{
	m_lineNum = _lineNum;
}

template <class T>
const T& TException_t<T>::GetObject()
{
	return m_object;
}

template <class T>
const string& TException_t<T>::GetMsg() const
{
	return m_msg;
}


template <class T>
const string& TException_t<T>::GetFileName() const
{
	return m_fileName;
}

template <class T>
unsigned int TException_t<T>::GetLineNum() const
{
	return m_lineNum;
}


#endif /* __TEXCEPTION_H__ */

