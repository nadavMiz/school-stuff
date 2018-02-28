#include <set>

#include "initializer.h"
#include "agentFactory.h"
#include "configParser.h"
#include "nlogFactory.h"

Initializer::Initializer(const std::string& _logPath)
{
	NlogFactory& logFactory = NlogFactory::GetNlogFactory();
	logFactory.setPath(_logPath);
	
	m_parser = new ConfigParser();
	m_agentFactory = new AgentFactory;
	m_log = logFactory.GetLog("system.log");
}

Initializer::~Initializer()
{
	delete m_agentFactory;
	delete m_parser;
}

void Initializer::Initialize(Hub* _hub, std::set<Agent*>& _agents, 
			const std::string& _configPath, const std::string& _soPath)
{
	m_agentFactory->SetPath(_soPath);
	m_parser->ParseFile(_configPath);
	
	AgentData data;
	Agent* agent;
	
	// while there are still agents to create
	while(true == (m_parser->GetNext(data)))
	{
		try
		{
			agent = m_agentFactory->CreateAgent(data, _hub);
			_agents.insert(agent);
		}
		catch(const exception& _err)
		{
			m_log->write(_err.what(), "initializer");
		}
	}
}

