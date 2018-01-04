#ifndef __INITIALIZER_H__
#define __INITIALIZER_H__

#include "sqlController.h"

#include <set>
#include <string>

class AgentFactory;
class ConfigParser;
class Hub;
class Agent;
class Nlog;

typedef std::tr1::shared_ptr<netcpp::SqlController> SqlControllerPtr;

class Initializer
{
public:
	Initializer(const std::string& _logPath);
	~Initializer();
	
	void LoadAgents(Hub* _hub, std::set<Agent*>& _agents, 
		SqlControllerPtr _dataBase, const std::string& _soPath);

private:
	/* data */
	AgentFactory* m_agentFactory;
	ConfigParser* m_parser;
	Nlog* m_log;
};

#endif /* __INITIALIZER_H__ */

