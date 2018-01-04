#ifndef __ANALIZER_H__
#define __ANALIZER_H__

#include <set>

#include "tokenizer.h"

using namespace std;

class analizer_t
{

	public:
		analizer_t(tokenizer_t* _tokenizer);
		virtual ~analizer_t (){};
		
		virtual void AnalizeLine(unsigned int _lineNum);
		virtual bool AnalizeFirstLines(unsigned int _lineNum); // return true if first line analasis ended
		void EndRoutine();
		
		void SetTokenizer(tokenizer_t* _tokenizer);
		
		static const string& GetGoodDelimiters() { return m_goodDelim;}

	protected:
		static set<string> m_types;
		static set<string> m_keyWords;
		static set<string> m_operators;
		static set<char> m_brackets;
		
		set<string> m_variables;
		unsigned int m_lineNum;
		
		// flags for SaveCurrentToken function
		bool m_isCombineWithPrev;
		bool m_IsForgetCurrentToken;

	protected:
		virtual void AnalizeToken(string& _token);
		virtual void PrintError(const string& _error);
		
		virtual void AnalizeMain(const string& _token);
		virtual void PrevTypeAnalizer(const string& _token);
		virtual void BracketAnalizer(const string& _token);
		virtual void KeywordAnalizer(const string& _token);
		virtual void OperatorAnalizer(const string& _token);
		virtual void VariableAnalizer(const string& _token);
		
		virtual void SaveCurrentToken(const string& _token);
		
		virtual void ClearMemmory();
		virtual void PrintSummary() const;
		
		bool IsNumber(const string& _token) const 
				{return (_token.find_first_not_of("0123456789") == string::npos);}
			
		bool IsVariableNameOk(const string& _token) const;
		
		static void SetGoodDelim(const string& _str) { m_goodDelim = _str;}

	private:
		/* data */
		tokenizer_t* m_tokenizer;
		bool m_IsPrevType;
		int m_numIfs;
		int m_numParentheses;
		int m_numSquareBrackets;
		int m_numCurrlyBrackets;
		string m_prevToken;
		
		static string m_goodDelim;
		
	private:
		analizer_t(const analizer_t& _analizer);
		analizer_t& operator=(const analizer_t& _analizer);
};

#endif /* __ANALIZER_H__ */

