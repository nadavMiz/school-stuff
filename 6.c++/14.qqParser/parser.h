#ifndef __PARSER_H__
#define __PARSER_H__

#include "analizer.h"
#include "tokenizer.h"

#include <string>
#include <iostream>
#include <fstream>

using namespace std;

class parser_t
{
	public:
		parser_t(const tokenizer_t* _tokenizer = 0, const analizer_t* _analizer = 0);
		virtual ~parser_t();
		
		virtual bool ParseFile(const string& _fileName);
	
	protected:
		virtual void AnalizeFile();
	
		ifstream m_file;
		tokenizer_t* m_tokenizer;
		analizer_t* m_analizer;
		unsigned int m_currentLine;
		
	private:
		parser_t(const parser_t& _parser);
		parser_t& operator=(const parser_t& _parser);
};

#endif /* __PARSER_H__ */

