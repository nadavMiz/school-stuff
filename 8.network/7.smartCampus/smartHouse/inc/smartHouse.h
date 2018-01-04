#ifndef __SMART_HOUSE_H__
#define __SMART_HOUSE_H__

#include <string>
#include <set>

#include "agent.h"
#include "nlogFactory.h"
#include "communicator.h"

class Hub;
class Initializer;

class SmartHouse
{
public:
	SmartHouse(const std::string& _configPath, const std::string& _soPath, const std::string& _logPath);
	virtual ~SmartHouse();
	
	virtual void Run();

private:
	/* data */
	std::string m_path;
	std::string m_soPath;
	Hub* m_hub;
	Initializer* m_initializer;
	std::set<Agent*> m_agents;
	NlogFactory* m_logFactory;
	smartCampus::Communicator m_communicator;
	
private:
	SmartHouse(const SmartHouse& _smartHouse);
	SmartHouse& operator=(const SmartHouse& _smartHouse);
};

#endif /* __SMART_HOUSE_H__ */

