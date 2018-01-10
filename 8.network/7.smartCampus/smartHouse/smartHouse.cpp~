#include "smartHouse.h"
#include "initializer.h"
#include "myHub.h"
#include "sqlController.h"

SmartHouse::SmartHouse(const std::string& _dataBase, const std::string& _soPath, const std::string& _logPath): 
	m_path(_dataBase)
,	m_soPath(_soPath)
,	m_initializer(new Initializer(_logPath))
,	m_hub(new MyHub)
,	m_communicator(m_hub.get())
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
	std::tr1::shared_ptr<netcpp::SqlController> dataBase(new netcpp::SqlController(m_path)); 
	m_initializer->LoadAgents(m_hub.get(), m_agents, dataBase, m_soPath);
}
