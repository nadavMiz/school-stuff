#include <iostream>
#include <cstdlib> /* atoi */
#include <cstring> /* strlen */

#include "smartClient.h"

const unsigned int MAX_MSG_SIZE = 1024;
const int PROBABILITY = 60;
const std::size_t NUM_CLIENTS = 1000;
const std::size_t NUM_ITERATIONS = 100; 

void ClientFunction(netcpp::ClientPtr _client)
{
	char msg[MAX_MSG_SIZE] = "client";
	try
	{
		_client->Send(msg, strlen(msg) + 1);
		
		_client->Recv(msg, MAX_MSG_SIZE);
		
		std::cout << "client " << _client->GetId() << " recived: " << msg << std::endl;
	}
	catch(const std::exception& _err)
	{
		std::cout << _err.what() << std::endl;
	}
}

int main(int argc, char* argv[])
{
	if(argc != 3)
	{
		std::cout << "invalid number of aguments" << std::endl;
		return 0;
	}
	
	netcpp::SmartClient smartClient(argv[2], atoi(argv[1]), ClientFunction, PROBABILITY, NUM_CLIENTS);
	
	smartClient.SmartClientRoutine(NUM_ITERATIONS);
	
	return 1;
}
