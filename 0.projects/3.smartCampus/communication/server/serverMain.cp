#include <cstring>
#include <iostream>
#include <cstdlib>

#include "server.h"
#include "serverSocket.h"

const unsigned int MAX_MSG_SIZE = 1024;

using namespace netcpp;

class ClientHandler: public IHandler
{
public:
	virtual ~ClientHandler(){}
	virtual EventStatus HandleEvent(SocketPtr _socket)
	{
		char reciveMsg[MAX_MSG_SIZE];
		char sendMsg[] = "server";
		ServerSocket* socket = dynamic_cast<ServerSocket*>(_socket.get());
		
		socket->Recv(reciveMsg, MAX_MSG_SIZE);
		std::cout << "client " << socket->GetId() << ": " << reciveMsg << std::endl;
		
		socket->Send(sendMsg, strlen(sendMsg) + 1);
		
		return e_statusOk;
	}
};


int main(int argc, char* argv[])
{
	if(argc != 2)
	{
		std::cerr << "invalid number of arguments" << std::endl; 
		return 0;
	}
	std::tr1::shared_ptr<ClientHandler> eventHandler(new ClientHandler);
	
	Server server(atoi(argv[1]), eventHandler);
	server.ServerRoutine();
	
	return 1;
}
