#include "configParser.h"

std::string ConfigParser::m_defaultLogName = "log.log";

ConfigParser::ConfigParser(): m_logFactory(NlogFactory::GetNlogFactory()), m_isEnd(false){}

void ConfigParser::ParseDataBase(SqlControllerPtr _dataBase)
{
	m_dataBase = _dataBase;
	m_currentResult = GetCurrentResult();
	m_isEnd = false;
}

Nlog* ConfigParser::GetLog(const std::string& _logName)
{
	if(_logName.empty())
	{
		return m_logFactory.GetLog(m_defaultLogName);
	}
	else
	{
		return m_logFactory.GetLog(_logName);
	}
}

bool ConfigParser::GetNext(AgentData& _data, std::string& _soName)
{	
	if(!m_currentResult->next())
	{
		m_isEnd = true;
		return false;
	}
	
	ResultSetPtr location = GetAgentLocation(m_currentResult->getInt("location_id"));
	ResultSetPtr typeinfo = GetAgentType(m_currentResult->getInt("type_id"));
	
	_data.m_id = m_currentResult->getString("id");
	_data.m_type = typeinfo->getString("agent_type");
	_data.m_room = location->getString("room");
	_data.m_floor = (unsigned int)location->getInt("floor");
	_data.m_config =  m_currentResult->getString("config");
	_data.m_log = GetLog(typeinfo->getString("log_name"));
	
	_soName = typeinfo->getString("so_name");
	
	return true;
}
