#include "smartHouse.h"
#include "initializer.h"
#include "myHub.h"
#include "sqlController.h"

SmartHouse::SmartHouse(const std::string& _dataBase, const std::string& _soPath, const std::string& _logPath): 
	m_soPath(_soPath)
,	m_dataBase(new netcpp::SqlController(_dataBase))
,	m_initializer(new Initializer(_logPath))
,	m_hub(new MyHub)
,	m_communicator(m_hub.get(), m_dataBase)
{}

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
	m_initializer->LoadAgents(m_hub.get(), m_agents, m_dataBase, m_soPath);
}
