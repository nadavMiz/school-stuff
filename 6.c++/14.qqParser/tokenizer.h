#ifndef __TOKENIZER_H__
#define __TOKENIZER_H__

#include <iostream>
#include <sstream> 
#include <deque>

using namespace std;

class tokenizer_t
{
	public:
		tokenizer_t(const string& _goodDelimiters = "", const string& _badDelimiters = " \t\n\r");
		virtual ~tokenizer_t(){};
		
		virtual void TokenLine(const string& _line);
		bool GetNext(string& _outString);
		
		void SetGoodDelimiters(const string& _delim);
		void SetBadDelimiters(const string& _delim);
		bool IsEndOfLine() const { return m_words.empty();}

	protected:
		/* data */
		string m_badDelimiters;
		string m_goodDelimiters;
		string m_delimiters;
		deque<string> m_words;
		size_t m_initialPos;
		
	protected:
		bool IsGoodDelimiter(char _charecter)
			 { return (m_goodDelimiters.find(_charecter) != string::npos);}
		
	private:
		tokenizer_t(const tokenizer_t& _tokenizer);
		tokenizer_t& operator=(const tokenizer_t& _tokenizer);
		
};

#endif /* __TOKENIZER_H__ */

