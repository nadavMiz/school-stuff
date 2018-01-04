#include "parser.h"
#include "tokenizer.h"
#include "analizer.h"

#include <string>
#include <new> //bad_alloc

using namespace std;

parser_t::parser_t(const tokenizer_t* _tokenizer, const analizer_t* _analizer)
{
	// initialize tokenizer
	if(0 == _tokenizer)
	{
		m_tokenizer = new tokenizer_t;
		if(0 == m_tokenizer)
		{
			throw new bad_alloc;
		}
	}
	else
	{
		m_tokenizer = (tokenizer_t*)_tokenizer;	
	}
	
	// initialize analizer
	if(0 == _analizer)
	{
		m_analizer = new analizer_t(m_tokenizer);
		if(0 == m_analizer)
		{
			throw new bad_alloc;
		}
	}
	else
	{
		m_analizer = (analizer_t*)_analizer;
	}
	
	// set tokenizers delimiters
	m_tokenizer->SetGoodDelimiters(m_analizer->GetGoodDelimiters());
}

parser_t::~parser_t()
{
	delete m_tokenizer;
	delete m_analizer;
}

void parser_t::AnalizeFile()
{
	unsigned int lineNum = 1;
	string line;
	bool isEndFirstLines = false;
	
	while(!m_file.eof() && !isEndFirstLines)
	{
		if(m_file.fail())
		{
			continue;
		}
		getline(m_file, line);
		m_tokenizer->TokenLine(line);
		isEndFirstLines = m_analizer->AnalizeFirstLines(lineNum);
		++lineNum;
	}
	
	while(!m_file.eof())
	{
		if(m_file.fail())
		{
			continue;
		}
		
		getline(m_file, line);
		m_tokenizer->TokenLine(line);
		m_analizer->AnalizeLine(lineNum);
		
		++lineNum;
	}
}

bool parser_t::ParseFile(const string& _fileName)
{	
	m_file.open(_fileName.c_str());
	
	if(m_file.fail())
	{
		return false;
	}
	
	AnalizeFile();
	
	m_analizer->EndRoutine();
	
	m_file.close();
	
	return true;
}
