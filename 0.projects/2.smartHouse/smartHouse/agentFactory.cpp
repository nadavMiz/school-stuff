#include <dlfcn.h>
#include <string>
#include <iostream>
#include <stdio.h>

#include "agentFactory.h"

const char* AgentFactory::m_creatorFunctionName = "CreateAgent";
const char* AgentFactory::m_soEnding = ".so";

Agent* AgentFactory::CreateAgent(const AgentData& _data, Hub* _hub)
{
	if(0 == _hub)
	{
		throw runtime_error("hub missing");
	}
	
	string fileName, deviceName;
	if(false == ParseId(_data.m_type, fileName, deviceName))
	{
		throw runtime_error("parsing error");
	}
	
	Creator creator = GetAgentCreator(fileName);

	return creator(deviceName ,_data, _hub);
}

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

bool AgentFactory::ParseId(const string& _agentId , string& _fileName, string& _deviceName)
{	
	
	// get the file name
	unsigned int pos;
	if(string::npos == (pos = _agentId.find('-')))
	{
		return false;
	}
	
	_fileName = _agentId.substr(0, pos);
	
	// get the device name
	++pos;
	unsigned int next;
	if(string::npos == (next = _agentId.find('-', pos)))
	{
		_deviceName = _agentId.substr(pos, _agentId.size() - pos);
	}
	else
	{
		_deviceName = _agentId.substr(pos, next - pos);
	}
	
	return true;
}

Creator AgentFactory::GetAgentCreator(const string& _fileName)
{
	// chack if the constructor is already in the map
	std::map<string, std::pair<Creator, void*> >::iterator itr;
	if(m_creators.end() != (itr = m_creators.find(_fileName)))
	{
		return itr->second.first;
	}
	
	// else get it from the so and insert it to the map
	string filePath = m_soPath + _fileName + m_soEnding;
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
