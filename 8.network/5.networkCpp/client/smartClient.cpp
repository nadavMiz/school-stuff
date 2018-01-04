#include <iostream>
#include <cstdlib> /* std::rand */

#include "smartClient.h"

namespace netcpp
{

SmartClient::SmartClient(const char* _ip, int _port, ClientFunction _func, int _probability, std::size_t _numClients):
	m_RunFunc(_func)
,	m_probability(_probability)
,	m_destIp(_ip)
,	m_destPort(_port)
,	m_numclients(_numClients)
{}

void SmartClient::RunAllClients()
{
	std::list<ClientPtr>::iterator clientItr = m_clients.begin();
	std::list<ClientPtr>::iterator nextItr = m_clients.begin();
	
	for(std::size_t i = 0; i < m_clients.size(); ++i, clientItr = nextItr)
	{
		++nextItr;
		RunSingleClient(clientItr);
	}	
}

void SmartClient::RunSingleClient(std::list<ClientPtr>::iterator _clientItr)
{
	if(std::rand()%100 < m_probability)
	{
		m_RunFunc(*_clientItr);
	}
	else
	{
		m_clients.erase(_clientItr);
	}
}

void SmartClient::CreateClients(std::size_t _numToCreate)
{
	try
	{
		for(std::size_t i = 0; i < _numToCreate; ++i)
		{
			if(std::rand()%100 < m_probability)
			{
				m_clients.push_back(ClientPtr(new ClientSocket(m_destIp, m_destPort)));
			}
		}
	}
	catch(const std::exception& _err)
	{
		std::cout << _err.what() << std::endl;
	}
}

void SmartClient::SmartClientRoutine(std::size_t _numIterations)
{
	std::size_t _numToCreate = 0;
	
	for(std::size_t i = 0; i < _numIterations; ++i)
	{
		_numToCreate = m_numclients - m_clients.size();
		
		RunAllClients();
		
		CreateClients(_numToCreate);
	}

}

}
