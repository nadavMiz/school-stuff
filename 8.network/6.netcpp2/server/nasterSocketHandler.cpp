#include <iostream>
#include <cstdio>

#include "masterSocketHandler.h"
#include "listenSocket.h"

namespace netcpp
{

MasterSocketHandler::MasterSocketHandler(ReactorPtr _reactor, IHandlerPtr _handler):
	m_reactor(_reactor)
,	m_handler(_handler){}

MasterSocketHandler::~MasterSocketHandler(){}

EventStatus MasterSocketHandler::HandleError(SocketPtr _socket)
{
	std::cout << "master socket error accured" << std::endl;
	return e_statusOk;
}


void MasterSocketHandler::LoadNewClients(SocketPtr _socket)
{	
	try
	{
		SocketPtr newSocket;
		ListenSocket* listenSocket = dynamic_cast<ListenSocket*>(_socket.get());
		
		while(true)
		{
			newSocket = listenSocket->Accept();
			m_reactor->AddSocket(newSocket, m_handler);
		}
	}
	catch(const std::underflow_error& _err){}
	catch(const std::exception& _err)
	{
		perror("accept error");
	}
}

EventStatus MasterSocketHandler::HandleEvent(SocketPtr _socket)
{
	LoadNewClients(_socket);
	
	return e_statusOk;
}

}
