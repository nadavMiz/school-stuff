#include <iostream> //cin + cout
#include <signal.h> //raise
#include <unistd.h> //getopt
#include <cstdlib> //exit(1)

#include "smartHouse.h"


struct Paths
{
	Paths():m_configPath("SmartBuilding"), m_soPath("sharedObjects/"), m_logPath("log/"){}
	
	std::string m_configPath;
	std::string m_soPath;
	std::string m_logPath;
};

void GetInput(int _argc, char** _argv, Paths& _paths)
{
	int opt;
	while ((opt = getopt(_argc, _argv, "c:p:l:?")) != -1)
	{
		switch(opt)
		{
			case 'c':
				_paths.m_configPath = optarg;
				break;
			case 's':
				_paths.m_soPath = optarg;
				break;
			case 'l':
				_paths.m_logPath = optarg;
				break;
			default:
				std::cout << "Usage: [-c config path] [-s so path] [-l log path]" << endl;
				exit(1);
	 	}
	 }
}

int main(int argc, char* argv[])
{
	unsigned int input;
	bool isRunning = true;
	Paths paths;
	
	GetInput(argc, argv, paths);
	
	try
	{
		SmartHouse smartHouse(paths.m_configPath, paths.m_soPath, paths.m_logPath);
		smartHouse.Run();
	
		while(isRunning)
		{
			cout << "enter 1 to send signal" << endl;
			cout << "any other number - quit" << endl;
			std::cin >> input;
		
			switch(input)
			{
				case 1:
					raise(SIGUSR2);
					break;
				
				default:
					isRunning = false;
					break;
			}
		}
	
	}
	catch(const std::exception& _err)
	{
		std::cout << "error: " << _err.what() <<endl;
		return 0;
	}
	
	return 1;
}

