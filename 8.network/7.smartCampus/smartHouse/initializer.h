#ifndef __INITIALIZER_H__
#define __INITIALIZER_H__

#include <set>
#include <string>

#include "iHubAPI.h"

class AgentFactory;
class IConfigParser;
class Agent;
class Nlog;

class Initializer
{
public:
	Initializer(const std::string& _logPath);
	~Initializer();
	
	void LoadAgents(smartCampus::IHubAPI* _hubAPI, std::set<Agent*>& _agents, 
		const std::string& _configPath, const std::string& _soPath);

private:
	/* data */
	AgentFactory* m_agentFactory;
	IConfigParser* m_parser;
	Nlog* m_log;
};

#endif /* __INITIALIZER_H__ */

