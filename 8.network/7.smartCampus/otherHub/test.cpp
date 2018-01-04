#include <unistd.h>
#include <cstring>

#include "clientSocket.h"

int main()
{
	char onmsg[] = "SHMP: event type:int topic:fire section:hub2 floor:5 room:6 agent:fire_alarm-6 data:1 ";
	char offmsg[] = "SHMP: event type:int topic:fire section:hub2 floor:5 room:6 agent:fire_alarm-6 data:0 ";
	
	sleep(1);
	netcpp::ClientSocket newSocket("127.0.0.1", 2001);
	for(int i = 0; i < 10; ++i)
	{
		sleep(1);
		newSocket.Send(onmsg, strlen(onmsg) + 1);
		sleep(1);
		newSocket.Send(offmsg, strlen(offmsg) + 1);
	}
}
