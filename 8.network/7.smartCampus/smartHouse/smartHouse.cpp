#include "smartHouse.h"
#include "initializer.h"
#include "hubImp.h"
#include "sqlController.h"

SmartHouse::SmartHouse(const std::string& _configPath, const std::string& _soPath, const std::string& _logPath):
	m_soPath(_soPath)
,	m_configPath(_configPath)
,	m_initializer(new Initializer(_logPath))
,	m_hub(new smartCampus::HubImp(_configPath))
,	m_communicator(m_hub.get(), _configPath)
{
	m_hub->ConnectCommunicator(&m_communicator);
}

SmartHouse::~SmartHouse()
{	
	for(std::set<Agent*>::iterator itr = m_agents.begin(); itr != m_agents.end(); ++itr)
	{
		delete *itr;
	}
}

void SmartHouse::Run()
{
	m_hub->ConnectCommunicator(&m_communicator);
	m_initializer->LoadAgents(m_hub.get(), m_agents, m_configPath, m_soPath);
}


