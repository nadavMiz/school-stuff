#include <string>
#include <deque>

#include "tokenizer.h"

using namespace std;

tokenizer_t::tokenizer_t(const string& _goodDelimiters, const string& _badDelimiters)
 :m_badDelimiters(_badDelimiters), m_goodDelimiters(_goodDelimiters)
{
	m_delimiters = _goodDelimiters + _badDelimiters;
}

void tokenizer_t::SetGoodDelimiters(const string& _delim)
{
	m_goodDelimiters = _delim;
	m_delimiters = m_goodDelimiters + m_badDelimiters;
}

void tokenizer_t::SetBadDelimiters(const string& _delim)
{
	m_badDelimiters = _delim;
	m_delimiters = m_goodDelimiters + m_badDelimiters;
}

void tokenizer_t::TokenLine(const string& _line)
{
	
	m_words.clear();
	
	size_t prev = 0, pos;
	
    while ((pos = _line.find_first_of(m_delimiters, prev)) != string::npos)
    {
        if (pos > prev)
        {
            m_words.push_back(_line.substr(prev, pos - prev));
        }
        if(IsGoodDelimiter(_line[pos]))
        {
           	m_words.push_back(_line.substr(pos, 1));
        }
        prev = pos + 1;
    }
    
    if (prev < _line.length())
    {
        m_words.push_back(_line.substr(prev, std::string::npos));
    }
    else if(IsGoodDelimiter(_line[pos]))
    {
       	m_words.push_back(_line.substr(pos, 1));
    }
}

bool tokenizer_t::GetNext(string& _outString)
{
	if(m_words.empty())
	{
		return false;
	}
	
	_outString = m_words[0];
	m_words.pop_front();
	return true;
}
