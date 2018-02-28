#ifndef __INITIALIZER_H__
#define __INITIALIZER_H__

#include <set>
#include <string>

class AgentFactory;
class ConfigParser;
class Hub;
class Agent;
class Nlog;

class Initializer
{
public:
	Initializer(const std::string& _logPath);
	virtual ~Initializer();
	
	virtual void Initialize(Hub* _hub, std::set<Agent*>& _agents, 
			const std::string& _configPath, const std::string& _soPath);

private:
	/* data */
	AgentFactory* m_agentFactory;
	ConfigParser* m_parser;
	Nlog* m_log;
	
};

#endif /* __INITIALIZER_H__ */

