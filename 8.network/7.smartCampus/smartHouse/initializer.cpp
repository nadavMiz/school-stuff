#include <set>

#include "initializer.h"
#include "agentFactory.h"
#include "dbConfigParser.h"
#include "nlogFactory.h"

Initializer::Initializer(const std::string& _logPath)
{
	NlogFactory& logFactory = NlogFactory::GetNlogFactory();
	logFactory.setPath(_logPath);
	
	m_parser = new DBConfigParser;
	m_agentFactory = new AgentFactory;
	m_log = logFactory.GetLog("system.log");
}

Initializer::~Initializer()
{
	delete m_agentFactory;
	delete m_parser;
}

void Initializer::LoadAgents(smartCampus::IHubAPI* _hubAPI, std::set<Agent*>& _agents, 
			const std::string& _configPath, const std::string& _soPath)
{
	m_agentFactory->SetPath(_soPath);
	m_parser->Parse(_configPath);
	
	AgentData data;
	std::string soName;
	Agent* agent;
	
	// while there are still agents to create
	while(m_parser->GetNext(data, soName))
	{
		try
		{
			agent = m_agentFactory->CreateAgent(data, soName, _hubAPI);
			_agents.insert(agent);
		}
		catch(const exception& _err)
		{
			m_log->write(_err.what(), "initializer");
		}
	}
}

