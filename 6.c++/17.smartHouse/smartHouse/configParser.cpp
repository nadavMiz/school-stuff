#include <iostream>
#include <sstream>
#include <string>
#include <stdexcept>

#include "configParser.h"

std::string ConfigParser::m_defaultLogName = "log.log";

ConfigParser::ConfigParser(): m_logFactory(NlogFactory::GetNlogFactory()){}

ConfigParser::~ConfigParser()
{
	if(m_file.is_open())
	{
		m_file.close();
	}
}

void ConfigParser::ClearAgentData(AgentData& _data)
{
	_data.m_type = "";
	_data.m_config = "";
	_data.m_log = 0;
}

void ConfigParser::ParseFile(const std::string& _fileName)
{
	if(m_file.is_open())
	{
		m_file.close();
	}
	
	m_file.open(_fileName.c_str());
	if(m_file.fail())
	{
		throw std::runtime_error("can't open config file");
	}
}

bool ConfigParser::GetNext(AgentData& _data)
{
	if(!m_file.is_open())
	{
		return false;
	}
	
	ClearAgentData(_data);
	
	std::string line;
	std::istringstream lineStream;
	
	while(getline(m_file, line))
	{
		lineStream.str(line);
		lineStream.clear();
		if(lineStream >> expect<'['> >> _data.m_id >> expect<']'>)
		{
			ParseSegment(_data);
			
			return true;
		}
	}
	return false;
}

void ConfigParser::ParseSegment(AgentData& _data)
{
	std::string line, type, logName;
	std::stringstream lineStream;
	
	while(getline(m_file, line))
	{
		lineStream.str(line);
		lineStream.clear();
		if(!(lineStream >> type >> expect<'='>))
		{
			break;
		}
		
		if("type" == type)
		{
			lineStream >> _data.m_type;
		}
		else if("room" == type)
		{
			lineStream >> _data.m_room;
		}
		else if("floor" == type)
		{
			lineStream >> _data.m_floor;
		}
		else if("config" == type)
		{
			getline(lineStream >> std::ws, _data.m_config);
		}
		else if("log" == type)
		{
			lineStream >> logName;
			_data.m_log = m_logFactory.GetLog(logName);
		}
		
	}
	
	if(0 == _data.m_log)
	{
		_data.m_log = m_logFactory.GetLog(m_defaultLogName);
	}
}
