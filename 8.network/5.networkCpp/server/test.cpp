#include <unistd.h>
#include <stdlib.h>
#include <cstring>
#include <iostream>
#include <pthread.h>
#include <stdio.h>

#include "server.h"
#include "timeValue.h"

using namespace netcpp;

void ServerFunction(void* _data, size_t _size, ClientPtr _client)
{
	char msg[] = "server";
	
	printf("msg recived from %d: %s\n", _client->GetId(), (char*)_data);
	
	if(_client->Send(msg, strlen(msg) + 1) < 0)
    {
        perror("msg send failed");
        return;
    }
}

int main(int argc, char* argv[])
{
	if(argc != 2)
	{
		std::cerr << "invalid number of arguments" << std::endl; 
		return 0;
	}
	TimeValue timeOut(1,0);
	
	Server server(atoi(argv[1]), ServerFunction, timeOut);
	server.ServerRoutine();
	
	return 1;
}
