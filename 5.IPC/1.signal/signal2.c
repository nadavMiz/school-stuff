#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>

#define SECOND 1000000

void SignalHandler(int sig, siginfo_t* _siginfo, void* _dummy)
{
	write(0, "process recived a signal\n\n", 26);
}

static void SetSignal(struct sigaction* _sa, int _signal)
{
	
	(*_sa).sa_sigaction = SignalHandler;
	(*_sa).sa_flags = SA_SIGINFO;
	sigemptyset(&((*_sa).sa_mask));
	if (sigaction(_signal, _sa, NULL) == -1)
	{
        perror("sigaction");
        exit(1);
    }
	
}

static void processFunction(int _otherSignal, int _otherPid, unsigned int _time, int _isParent)
{
	int myPid = getpid();
	if(_isParent)
	{
		sleep(1);
    	kill(_otherPid, _otherSignal);
    	printf("process: %d sent signal: %d to process: %d\n", myPid, _otherSignal, _otherPid);
	}
	
    while(1)
    {
    	pause();
    	usleep(_time);
    	kill(_otherPid, _otherSignal);
    	printf("process: %d sent signal: %d to process: %d\n", myPid, _otherSignal, _otherPid);
    } 
}

int main(int argc, char *argv[])
{
	struct sigaction sa;
	int parentSignal = SIGUSR1;
	int childSignal = SIGUSR1;
	extern char *optarg;
	int pid, opt;
	unsigned int time = SECOND;
	
	/*read input*/
	while ((opt = getopt(argc, argv, "p:c:s:")) != -1)
	{
		switch(opt)
		{
			case 'p':
				parentSignal = atoi(optarg);
				break;
			case 'c':
				childSignal = atoi(optarg);
				break;
			case 's':
				time = (unsigned int)atoi(optarg);
				break;
	 	}
	}
	
	SetSignal(&sa, parentSignal);
	/*make new process and run it*/
	pid = fork();
	if(pid < 0)
	{
		perror("fork");
	}
	else if(pid > 0)
	{
		processFunction(childSignal, pid, time, 1);
	}
	else
	{
		/*set child signal*/
		if (sigaction(childSignal, &sa, NULL) == -1)
		{
		    perror("sigaction");
		    exit(1);
		}
		processFunction(parentSignal, getppid(), time, 0);
	}
	return 0;
}
