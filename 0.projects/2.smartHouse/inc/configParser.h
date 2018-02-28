#ifndef __CONFIG_PARSER_H__
#define __CONFIG_PARSER_H__

#include <iostream>
#include <sstream>
#include <string>
#include <fstream>

#include "agentData.h"
#include "nlogFactory.h"
#include "nlog.h"

class ConfigParser
{
public:
	ConfigParser();
	virtual ~ConfigParser();
	
	virtual void ParseFile(const std::string& _fileName);
	virtual bool GetNext(AgentData& _data);
	
	bool IsEndOfFile() const { return (!m_file.is_open() || m_file.eof());}
	static void SetDefaultLogName(const std::string& _newName) {m_defaultLogName = _newName;}

protected:
	virtual void ParseSegment(AgentData& _data);
	virtual void ClearAgentData(AgentData& _data);
	
	template <char C>
	static std::istream& expect(std::istream& in);

protected:
	/* data */
	std::ifstream m_file;
	NlogFactory& m_logFactory;
	
	static std::string m_defaultLogName;

private:
	ConfigParser(const ConfigParser& _parser);
	ConfigParser& operator=(const ConfigParser& _parser);

};

template <char C>
std::istream& ConfigParser::expect(std::istream& in)
{
    if ((in >> std::ws).peek() == C) 
    {
        in.ignore();
    }
    else 
    {
        in.setstate(std::ios_base::failbit);
    }
    return in;
}

#endif /* __CONFIG_PARSER_H__ */

