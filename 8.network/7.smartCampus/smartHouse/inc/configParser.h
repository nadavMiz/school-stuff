#ifndef CONFIG_PARSER_H
#define CONFIG_PARSER_H

#include <string>
#include <sstream> //stringstream

#include "uncopyable.h"
#include "sqlController.h"
#include "agentData.h"
#include "nlogFactory.h"
#include "nlog.h"

typedef std::tr1::shared_ptr<netcpp::SqlController> SqlControllerPtr;

class ConfigParser: private Uncopyable
{
public:
	ConfigParser();
	//~ConfigParser(); default DTOR
	
	void ParseDataBase(SqlControllerPtr _dataBase);
	bool GetNext(AgentData& _data, std::string& _soName);
	
	inline bool IsEndOfFile() const;
	inline static void SetDefaultLogName(const std::string& _newName);
	
private:
	inline ResultSetPtr GetCurrentResult();	
	inline ResultSetPtr GetAgentLocation(int _id);
	inline ResultSetPtr GetAgentType(int _id);
	Nlog* GetLog(const std::string& _logName);

private:
	SqlControllerPtr m_dataBase;
	ResultSetPtr m_currentResult;
	NlogFactory& m_logFactory;
	bool m_isEnd;
	
	static std::string m_defaultLogName;
};

inline bool ConfigParser::IsEndOfFile() const
{
	return m_isEnd;
}

inline void ConfigParser::SetDefaultLogName(const std::string& _newName) 
{
	m_defaultLogName = _newName;
}

inline ResultSetPtr ConfigParser::GetCurrentResult()
{
	return m_dataBase->Query("SELECT * FROM Agents");
}

inline ResultSetPtr ConfigParser::GetAgentLocation(int _id)
{
	std::stringstream quary;
	quary << "SELECT * FROM Location WHERE id = " << _id;
	ResultSetPtr result = m_dataBase->Query(quary.str());
	result->next();
	return result;
}

inline ResultSetPtr ConfigParser::GetAgentType(int _id)
{
	std::stringstream quary;
	quary << "SELECT * FROM AgentType WHERE id = " << _id;
	ResultSetPtr result = m_dataBase->Query(quary.str());
	result->next();
	return result;
}

#endif /* CONFIG_PARSER_H */

