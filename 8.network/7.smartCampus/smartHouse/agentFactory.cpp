#include <dlfcn.h>

#include "agentFactory.h"

const char* AgentFactory::m_creatorFunctionName = "CreateAgent";

const char* AgentFactory::DEFAULT_SO_PATH = "";

AgentFactory::AgentFactory(const std::string& _soPath): m_soPath(_soPath){}

AgentFactory::~AgentFactory()
{
	std::map<string, std::pair<Creator, void*> >::iterator itr;
	for(itr = m_creators.begin(); itr != m_creators.end(); ++itr)
	{
		if(0 != dlclose(itr->second.second))
		{
			fprintf(stderr, "dlclose: %s \n", dlerror());
		}
	}
}

/*----------------------------------------------------------------------------*/

Creator AgentFactory::GetAgentCreator(const string& _fileName)
{
	// chack if the constructor is already in the map
	std::map<string, std::pair<Creator, void*> >::iterator itr;
	if(m_creators.end() != (itr = m_creators.find(_fileName)))
	{
		return itr->second.first;
	}
	
	// else get it from the so and insert it to the map
	string filePath = m_soPath + _fileName;
	void* soHandle = dlopen(filePath.c_str(), RTLD_LAZY);
	if(0 == soHandle)
	{
		throw runtime_error(dlerror());
	}	
	
	Creator creator = (Creator)dlsym(soHandle, m_creatorFunctionName);
	if(0 == creator)
	{
		throw runtime_error(dlerror());
	}	
	
	std::pair<Creator, void*> newPair(creator, soHandle);
	
	m_creators.insert(std::pair<string, std::pair<Creator, void*> >(_fileName, newPair));
	
	return creator;
}

/*----------------------------------------------------------------------------*/

Agent* AgentFactory::CreateAgent(const AgentData& _data, const string& _soName, Hub* _hub)
{
	if(0 == _hub)
	{
		throw runtime_error("hub missing");
	}
	
	Creator creator = GetAgentCreator(_soName);

	return creator(_data.m_type , _data, _hub);
}
