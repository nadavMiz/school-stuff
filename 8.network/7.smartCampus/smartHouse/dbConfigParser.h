#ifndef DB_CONFIG_PARSER_H
#define DB_CONFIG_PARSER_H

#include <string>
#include <tr1/memory>

#include "iConfigParser.h"
#include "sqlController.h"
#include "agentData.h"
#include "nlogFactory.h"

typedef std::tr1::shared_ptr<netcpp::SqlController> SqlControllerPtr;

class DBConfigParser: public IConfigParser
{
public:
	DBConfigParser();
	//~DBConfigParser(); default DTOR
	
	virtual void Parse(const std::string& _consfigPath);
	virtual bool GetNext(AgentData& _data, std::string& _soName);
	
	virtual bool IsEndOfFile() const;
	//static void SetDefaultLogName(const std::string& _newName);

protected:
	//inline const std::string& GetDefaultLogName();
	
private:
	ResultSetPtr GetCurrentResult();	
	ResultSetPtr GetAgentLocation(int _id);
	ResultSetPtr GetAgentType(int _id);
	Nlog* GetLog(const std::string& _logName);

private:
	SqlControllerPtr m_dataBase;
	ResultSetPtr m_currentResult;
	NlogFactory& m_logFactory;
	bool m_isEnd;
	
	//static std::string m_defaultLogName;
};

inline bool DBConfigParser::IsEndOfFile() const
{
	return m_isEnd;
}

#endif /* DB_CONFIG_PARSER_H */

