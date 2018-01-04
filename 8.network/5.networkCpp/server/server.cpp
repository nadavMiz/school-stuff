#include <cstddef> // std::size_t
#include <errno.h> // errno
#include <stdio.h> // perror
#include <stdexcept> // exceptions
#include <iostream> // debugging
	
#include "server.h"
#include "netExceptions.h"

const std::size_t MAX_MSG_SIZE = 1024;
const std::size_t MAX_CLIENTS = 1000;

namespace netcpp
{

Server::Server(int _port, RunFunction _runFunc, const TimeValue& _timeOut, std::size_t _backlogSize):
	m_masterSocket(_port, _backlogSize)
,	m_RunFunc(_runFunc)
,	m_backlogSize(_backlogSize)
,	m_timeOut(_timeOut)
{
	m_masterSocket.SetNoBlock();
	m_selectSet.Set(m_masterSocket);
}

void Server::LoadNewClients()
{
	SocketPtr newSocket;
	
	try
	{
		while(true)
		{
			newSocket = m_masterSocket.Accept();
			if(m_clients.size() != MAX_CLIENTS)
			{
				AddClient(newSocket);
			}
		}
	}
	catch(const std::underflow_error& _err){}
	catch(const std::exception& _err)
	{
		perror("accept error");
	}
}

void Server::UpdateClientTimeOut(std::list<ClientPtr>::iterator _clientItr)
{
	ClientPtr client = (*_clientItr);
	
	client->m_timeOut = m_nextTime;
	
	/*move client to the end of the list*/
	m_clients.erase(_clientItr);
	m_clients.push_back(client);
}

void Server::ClientRoutine(void* _msg, std::size_t _msgSize, std::list<ClientPtr>::iterator _clientItr)
{	
	m_RunFunc(_msg, _msgSize, *_clientItr);
	if(!((*_clientItr)->m_isActive))
	{
		RemoveClient(_clientItr);
		return;
	}
	
	UpdateClientTimeOut(_clientItr);
}

void Server::AddClient(SocketPtr _socket)
{
	ClientPtr newClient(new ServersClient(_socket, m_nextTime));
	m_clients.push_back(newClient);
	m_selectSet.Set(*_socket);
}

void Server::RemoveClient(std::list<ClientPtr>::iterator _clientItr)
{
	m_selectSet.ClearOne(*(*_clientItr)->m_socket);
	m_clients.erase(_clientItr);
}

void Server::HandleClientMsgError(std::list<ClientPtr>::iterator _clientItr)
{
	perror("ERROR on accept");
	RemoveClient(_clientItr);
}

void Server::HanleSingleClient(std::list<ClientPtr>::iterator _clientItr)
{
	char msg[MAX_MSG_SIZE];
	try
	{
		ssize_t count = (*_clientItr)->Recv(msg, MAX_MSG_SIZE, CommSocket::e_noWait);
		
		ClientRoutine(msg, (size_t)count, _clientItr);
	}
	/* client has disconnected */
	catch(const BrokenPipe_error& _err)
	{
		RemoveClient(_clientItr);
	}
	/*error has accured*/
	catch(const std::exception& _err)
	{
		HandleClientMsgError(_clientItr);
	}
}

void Server::HandleAllClients(unsigned int _numActiveSockets)
{
	std::list<ClientPtr>::iterator clientItr, nextItr;
	
	for(clientItr = nextItr = m_clients.begin(); 0 < _numActiveSockets; clientItr = nextItr)
	{
		++nextItr;
		if(m_selectSet.IsSet(*(*clientItr)->m_socket))
		{
			HanleSingleClient(clientItr);
			--_numActiveSockets;
		}
	}
}

void Server::UpdateNextTime()
{
	TimeValue currentTime;
	currentTime.SetToCurrentTime();
	
	m_nextTime = currentTime + m_timeOut;
}

TimeValue Server::GetNextTimeToWait()
{	
	TimeValue currentTime;
	currentTime.SetToCurrentTime();
	
	ClientPtr nextClient = m_clients.front();
	
	TimeValue nextTime = nextClient->m_timeOut - currentTime;
	
	if(nextTime.IsNegative())
	{
		nextTime.Clear();
	}
	return nextTime;
}

unsigned int Server::WaitForActivity()
{
	if(m_clients.empty())
	{
		return m_selectSet.Wait();
	}
	else
	{
		TimeValue timeToWait = GetNextTimeToWait();
		return m_selectSet.WaitUntil(timeToWait);
	}
}

void Server::RemoveAllInactiveClients()
{
	TimeValue currentTime;
	std::list<ClientPtr>::iterator clientItr;
	
	currentTime.SetToCurrentTime();
	
	while(!m_clients.empty())
	{
		clientItr = m_clients.begin();
		
		if(currentTime > (*clientItr)->m_timeOut)
		{
			std::cout << "clientRemoved" << std::endl;
			RemoveClient(clientItr);
		}
		else
		{
			break;
		}
	}
}

void Server::ServerRoutine()
{
	unsigned int NumActiveSockets;
	
	while(true)
	{
		NumActiveSockets = WaitForActivity();
		
		/*client has timed out*/
		if(0 == NumActiveSockets)
		{
			RemoveAllInactiveClients();
			continue;
		}
		
		UpdateNextTime();
		/* new clients trying to connect */
		if(m_selectSet.IsSet(m_masterSocket))
		{
			LoadNewClients();
			--NumActiveSockets;
		}
		
		HandleAllClients(NumActiveSockets);
	}
}

}
