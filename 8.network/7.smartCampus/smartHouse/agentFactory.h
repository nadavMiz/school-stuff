#ifndef AGET_FACTORY_H
#define AGET_FACTORY_H

#include <map>
#include <string>
#include <string>
#include <tr1/memory>

#include "uncopyable.h"
#include "agent.h"
#include "agentData.h"
#include "iHubAPI.h"

typedef Agent* (*Creator) (const string& _deviceName, const AgentData& _data, smartCampus::IHubAPI* _hubAPI);

class AgentFactory: private Uncopyable
{
public:
	AgentFactory(const std::string& _soPath = DEFAULT_SO_PATH);
	~AgentFactory();
	
	Agent* CreateAgent(const AgentData& _data, const string& _soName, smartCampus::IHubAPI* _hubAPI);
	void SetPath(const string& _path);

private:
	Creator GetAgentCreator(const string& _fileName);

private:
	/* data */
	std::map<string, std::pair<Creator, void*> > m_creators;
	std::string m_soPath;
	
	static const char* m_creatorFunctionName;
	static const char* DEFAULT_SO_PATH;
};

inline void AgentFactory::SetPath(const string& _path)
{
	m_soPath = _path;
}

#endif /* AGET_FACTORY_H */

