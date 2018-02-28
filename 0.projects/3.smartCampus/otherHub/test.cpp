#include <unistd.h>
#include <cstring>
#include <iostream>
#include <pthread.h>

#include "clientSocket.h"
#include "listenSocket.h"

#define MSG_LENGTH 1024

void* threadfunc(void* _dummy)
{
	char request[] = "SHMP: subscribe section:otherHub topic:fire floor:5";
	char response[MSG_LENGTH];
	
	/*create connection*/
	netcpp::ListenSocket listener(5000);
	netcpp::ClientSocket newSocket("127.0.0.1", 2003);
	
	newSocket.Send(request, strlen(request) + 1);
	
	std::tr1::shared_ptr<netcpp::ServerSocket> socket = listener.Accept();
	
	newSocket.Recv(response, MSG_LENGTH);
	std::cout << response << std::endl;

	/*get events*/
	
	for(int i = 0; i < 6; ++i)
	{
		socket->Recv(response, MSG_LENGTH);
		std::cout << response << std::endl;
	}
	socket->Disconnect();
	listener.CloseSocket();
	return 0;
}

int main()
{
	char onmsg[] = "SHMP: event type:int topic:fire section:hub2 floor:5 room:6 agent:fire_alarm-6 data:1";
	char offmsg[] = "SHMP: event type:int topic:fire section:hub2 floor:5 room:6 agent:fire_alarm-6 data:0";
	char response[MSG_LENGTH];
	pthread_t thread;
	
	pthread_create(&thread, NULL, threadfunc, NULL);
	
	sleep(1);
	netcpp::ClientSocket newSocket("127.0.0.1", 2004);
	for(int i = 0; i < 3; ++i)
	{
		sleep(1);
		newSocket.Send(onmsg, strlen(onmsg) + 1);
		newSocket.Recv(response, MSG_LENGTH);
		//std::cout << response << std::endl;
		
		sleep(1);
		newSocket.Send(offmsg, strlen(offmsg) + 1);
		newSocket.Recv(response, MSG_LENGTH);
		//std::cout << response << std::endl;
	}
	pthread_join(thread, NULL);
	newSocket.Disconnect();
	
	return 1;
}
