#include "smartHouse.h"
#include "initializer.h"
#include "myHub.h"

SmartHouse::SmartHouse(const std::string& _configPath, const std::string& _soPath, const std::string& _logPath): 
						m_path(_configPath), m_soPath(_soPath)
{
	m_initializer = new Initializer(_logPath);
	m_hub = new MyHub;
}

SmartHouse::~SmartHouse()
{	
	for(std::set<Agent*>::iterator itr = m_agents.begin(); itr != m_agents.end(); ++itr)
	{
		delete *itr;
	}
	delete m_hub;
	delete m_initializer;
}

void SmartHouse::Run()
{
	m_initializer->Initialize(m_hub, m_agents, m_path, m_soPath);
}
