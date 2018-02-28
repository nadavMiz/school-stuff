#ifndef __AGENT_FACTORY_H__
#define __AGENT_FACTORY_H__

#include <map>
#include <string>

#include "agent.h"
#include "agentData.h"

typedef Agent* (*Creator) (const string& _deviceName, const AgentData& _data, Hub* _hub);

class AgentFactory
{
	public:
		AgentFactory(const std::string& _soPath = ""): m_soPath(_soPath){};
		virtual ~AgentFactory();
		
		virtual Agent* CreateAgent(const AgentData& _data, Hub* _hub);
		
		void SetPath(const string& _path) { m_soPath = _path;}

	private:
		/* data */
		std::map<string, std::pair<Creator, void*> > m_creators;
		std::string m_soPath;
		
		static const char* m_creatorFunctionName;
		static const char* m_soEnding;
		
	private:
		bool ParseId(const string& _id , string& _fileName, string& _funcName);
		Creator GetAgentCreator(const string& _fileName);
	
		AgentFactory(const AgentFactory& _factory);
		AgentFactory& operator=(const AgentFactory& _factory);
};

#endif /* __AGENT_FACTORY_H__ */

