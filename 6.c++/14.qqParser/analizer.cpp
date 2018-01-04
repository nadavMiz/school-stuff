#include <iostream>
#include <cctype>

#include "analizer.h"
#include "tokenizer.h"

using namespace std;


string analizer_t::m_goodDelim = "()[]{};<>=+-*&,";

const string types[] = {"char", "short", "int", "float", "double", "void"};
const string keyWords[] = {"if", "else", "for", "while", "class", "private", "public",
						   "protected", "main", "const", "virtual", ";"};
const string operators[] = {"++", "--", "==", "-", "=", "+", "-", "*", "&", "<", ">"};
const char brakets[] = {'(', ')', '[', ']', '{', '}'};

set<string> analizer_t::m_types(types, types + sizeof(types) / sizeof(types[0]));
set<string> analizer_t::m_keyWords(keyWords, keyWords + sizeof(keyWords) / sizeof(keyWords[0]));
set<string> analizer_t::m_operators(operators, operators + sizeof(operators) / sizeof(operators[0]));
set<char> analizer_t::m_brackets(brakets, brakets + sizeof(brakets) / sizeof(brakets[0]));


analizer_t::analizer_t(tokenizer_t* _tokenizer) 
{
	m_tokenizer = _tokenizer;
	
	ClearMemmory();
}

void analizer_t::ClearMemmory()
{
	m_IsPrevType = false;
	m_numIfs = 0;
	m_numParentheses = 0;
	m_numSquareBrackets = 0;
	m_numCurrlyBrackets = 0;
	m_isCombineWithPrev = 0;
	m_IsForgetCurrentToken = 0;
	m_prevToken = "";
	m_lineNum = 1;
	m_variables.clear();
}

void analizer_t::SetTokenizer(tokenizer_t* _tokenizer)
{
	 if(0 != _tokenizer)
	 {
	 	m_tokenizer = _tokenizer;
	 } 
}

void analizer_t::AnalizeLine(unsigned int _lineNum)
{
	if(0 == m_tokenizer)
	{
		return;
	}
	
	m_lineNum = _lineNum;
	string token;
	
	while(m_tokenizer->GetNext(token))
	{
		
		AnalizeToken(token);
		
		SaveCurrentToken(token);
	}
}

bool analizer_t::AnalizeFirstLines(unsigned int _lineNum)
{
	if(0 == m_tokenizer)
	{
		return false;
	}
	
	string token;
	
	if(m_tokenizer->GetNext(token))
	{
		m_lineNum = _lineNum;
	
		AnalizeMain(token);
		
		// first token might have more errors besides not being main
		AnalizeToken(token);
		
		AnalizeLine(_lineNum);
		
		return true;
	}
	
	return false;
	
}

void analizer_t::AnalizeMain(const string& _token)
{
	if(_token != "main")
	{
		PrintError(("undefined refrence to main"));
	}
}

void analizer_t::SaveCurrentToken(const string& _token)
{
	if(m_isCombineWithPrev)
	{
		m_prevToken += _token;
		m_isCombineWithPrev = false;
	}
	else if(m_IsForgetCurrentToken)
	{
		m_prevToken = "";
		m_IsForgetCurrentToken = false;
	}
	else
	{
		m_prevToken = _token;
	}
}

void analizer_t::AnalizeToken(string& _token)
{
	//previous toke was type
	if(m_IsPrevType)
	{
		PrevTypeAnalizer(_token);
		m_IsPrevType = false;
		return;
	}
	
	else if(m_types.end() != m_types.find(_token))
	{
		m_IsPrevType = true;
		return;
	}
	
	else if(m_brackets.end() != m_brackets.find(_token[0]))
	{
		BracketAnalizer(_token);
		return;
	}
	
	else if(m_keyWords.end() != m_keyWords.find(_token))
	{
		KeywordAnalizer(_token);
		return;
	}
	
	else if(m_operators.end() != m_operators.find(_token))
	{
		OperatorAnalizer(_token);
		return;
	}
	
	else if(IsNumber(_token))
	{
		return;
	}
	
	else
	{
		VariableAnalizer(_token);
		return;
	}
}

void analizer_t::KeywordAnalizer(const string& _token)
{
	if("if" == _token)
	{
		++m_numIfs;
		return;
	}
	else if("else" == _token)
	{
		if(0 == m_numIfs)
		{
			PrintError(("'else' without 'if'"));
		}
		else
		{
			--m_numIfs;
		}
		return;
	}
}

void analizer_t::PrintError(const string& _error)
{
	cout << "error in line " << m_lineNum << ": " << _error << endl; 
}

bool analizer_t::IsVariableNameOk(const string& _token) const
{
	if(!isalpha(_token[0]) && ('_' != _token[0]))
	{
		return false;
	}
	
	for(unsigned int i = 0; i < _token.size(); ++i)
	{
		if(!isalnum(_token[i]) && ('_' != _token[i]))
		{
			return false;
		}
	}
	
	return true;
}

void analizer_t::PrevTypeAnalizer(const string& _token)
{
	if(m_types.end() != m_types.find(_token))
	{
		PrintError(("multiple type decleration"));
	}
	else if(m_keyWords.end() != m_keyWords.find(_token))
	{
		PrintError(("keyword after type"));
	}
	else if(m_operators.end() != m_operators.find(_token))
	{
		PrintError(("operator after type"));
	}
	else if(!IsVariableNameOk(_token))
	{
		PrintError(("invalid variable name: " + _token));
	}
	else if(m_variables.end() != m_variables.find(_token))
	{
		PrintError(("variable already declared"));
	}
	else
	{
		m_variables.insert(_token);
	}
}

void analizer_t::BracketAnalizer(const string& _token)
{
	switch(_token[0])
	{
		case '(':
			++m_numParentheses;
			break;
		
		case '[':
			++m_numSquareBrackets;
			break;
			
		case '{':
			++m_numCurrlyBrackets;
			break;
			
		case ')':
			if(0 == m_numParentheses)
			{
				PrintError("expected '(' before ')' ");
			}
			else
			{
				--m_numParentheses;
			}
			break;
			
		case ']':
			if(0 == m_numSquareBrackets)
			{
				PrintError("expected '[' before ']' ");
			}
			else
			{
				--m_numSquareBrackets;
			}
			break;
			
		case '}':
			if(0 == m_numCurrlyBrackets)
			{
				PrintError("expected '{' before '}' ");
			}
			else
			{
				--m_numCurrlyBrackets;
			}
			break;
	}
}

void analizer_t::OperatorAnalizer(const string& _token)
{
	if("+" == _token)
	{
		if("+" == m_prevToken)
		{
			m_isCombineWithPrev = true;
		}
		else if("++" == m_prevToken)
		{
			PrintError("invalid operator '+++' ");
			m_IsForgetCurrentToken = true;
		}
		
		return;
	}
	
	if("-" == _token)
	{
		if("-" == m_prevToken)
		{
			m_isCombineWithPrev = true;
		}
		else if("--" == m_prevToken)
		{
			PrintError("invalid operator '---' ");
			m_IsForgetCurrentToken = true;
		}
		
		return;
	}
}

void analizer_t::VariableAnalizer(const string& _token)
{
	if(m_variables.end() == m_variables.find(_token))
	{
		PrintError("undefined variable: " + _token);
	}
}

void analizer_t::PrintSummary() const
{
	if(m_numParentheses > 0)
	{
		cout << "error - " << m_numParentheses << " '(' not closed" << endl;
	}
	if(m_numSquareBrackets > 0)
	{
		cout << "error - " << m_numSquareBrackets << " '[' not closed" << endl;
	}
	if(m_numCurrlyBrackets > 0)
	{
		cout << "error - " << m_numCurrlyBrackets << " '{' not closed" << endl;
	}
}

void analizer_t::EndRoutine()
{
	PrintSummary();
	
	ClearMemmory();
}

