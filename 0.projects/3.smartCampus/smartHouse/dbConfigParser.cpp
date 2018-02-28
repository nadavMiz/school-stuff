#include <sstream>

#include "dbConfigParser.h"

DBConfigParser::DBConfigParser(): m_logFactory(NlogFactory::GetNlogFactory()), m_isEnd(false){}

void DBConfigParser::Parse(const std::string& _consfigPath)
{
	m_dataBase = SqlControllerPtr(new netcpp::SqlController(_consfigPath));
	m_currentResult = GetCurrentResult();
	m_isEnd = false;
}

Nlog* DBConfigParser::GetLog(const std::string& _logName)
{
	if(_logName.empty())
	{
		return m_logFactory.GetLog(GetDefaultLogName());
	}
	else
	{
		return m_logFactory.GetLog(_logName);
	}
}

ResultSetPtr DBConfigParser::GetCurrentResult()
{
	return m_dataBase->Query("SELECT * FROM Agents");
}

ResultSetPtr DBConfigParser::GetAgentLocation(int _id)
{
	std::stringstream quary;
	quary << "SELECT * FROM Location WHERE id = " << _id;
	ResultSetPtr result = m_dataBase->Query(quary.str());
	result->next();
	return result;
}

ResultSetPtr DBConfigParser::GetAgentType(int _id)
{
	std::stringstream quary;
	quary << "SELECT * FROM AgentType WHERE id = " << _id;
	ResultSetPtr result = m_dataBase->Query(quary.str());
	result->next();
	return result;
}

bool DBConfigParser::GetNext(AgentData& _data, std::string& _soName)
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
