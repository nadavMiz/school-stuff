#include <cstdio>
#include <iostream>
#include <unistd.h>

#include "server.h"
#include "serverSocket.h"
#include "clientSocket.h"
#include "nthread.h"
#include "mu_test.h"
#include "ihandler.h"

using namespace netcpp;

using namespace advcpp::sync;

int g_port = 5554;

const unsigned int MAX_MSG = 1024;

/*----------------------------------------------------------------------*/

class ClientHandler: public IHandler
{
public:
	virtual ~ClientHandler(){}
	virtual EventStatus HandleEvent(SocketPtr _socket)
	{
		try
		{
		char msg[1024];
		ServerSocket* socket = dynamic_cast<ServerSocket*>(_socket.get());
		socket->Recv(&msg, 1024);
		std::cout << socket->GetId() << ": " << msg << std::endl;
		return e_statusOk;
		}
		catch(std::exception& _err)
		{
			return e_statusToDelete;
		}
	}
};

/*----------------------------------------------------------------------*/

struct ServerFunc
{
	void Run()
	{
		std::tr1::shared_ptr<IHandler> handler(new ClientHandler);
		TimeValue value;
		Server server(g_port, handler, value);
	
		server.ServerRoutine();
	}
};

/*----------------------------------------------------------------------*/

struct ClientFunc
{
	ClientFunc(int _numIterations): m_data(0), m_numIterations(_numIterations){}
	
	void Run()
	{
		ClientSocket client0("127.0.0.1", g_port);
		char msg1[100] = "nadav";
		char msg2[100] = " is da best";
	
		client0.Send(msg1, strlen(msg1));
		client0.Send(msg2, strlen(msg2) + 1);
	}
	int m_data;
	int m_numIterations;
};

/*----------------------------------------------------------------------*/

UNIT(reactor)
int numIteratiorns = 1000;

std::tr1::shared_ptr<ServerFunc> myServer(new ServerFunc);
std::tr1::shared_ptr<ClientFunc> myClient(new ClientFunc(numIteratiorns));

Nthread<ServerFunc> server(myServer, &ServerFunc::Run);
sleep(1);
Nthread<ClientFunc> client(myClient, &ClientFunc::Run);

client.Join();

server.Detach();
std::cout << myClient->m_data << std::endl;
ASSERT_THAT(myClient->m_data == (numIteratiorns * 6));

END_UNIT

TEST_SUITE(server)

TEST(reactor)

END_SUITE
