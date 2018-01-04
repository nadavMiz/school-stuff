#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>


volatile sig_atomic_t g_parentSignal = SIGUSR1;
volatile sig_atomic_t g_childSignal = SIGUSR1;
volatile sig_atomic_t g_time = 1000000;

void SignalHandlerChild(int sig, siginfo_t* _siginfo, void* _dummy)
{
	write(0, "child recived signal from parent\n\n", 35);
	usleep((unsigned int)g_time);
    kill(_siginfo->si_pid, g_parentSignal);
    write(0, "child sent signal to parent\n", 29);
}

void SignalHandlerParent(int sig, siginfo_t* _siginfo, void* _dummy)
{
	write(0, "parent recived signal from child\n\n", 35);
	usleep((unsigned int)g_time);
    kill(_siginfo->si_pid, g_childSignal);
    write(0, "parent sent signal to child\n", 29);
}

static void SetSignal(int _signal, void (*sasigaction)(int, siginfo_t *, void * _dummy))
{
	struct sigaction sa;
	
	sa.sa_sigaction = sasigaction;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&(sa.sa_mask));
	if (sigaction(_signal, &sa, NULL) == -1)
	{
        perror("sigaction");
        exit(1);
    }
	
}

static void ParentFunction(int childPid)
{
	SetSignal(g_parentSignal, SignalHandlerParent);
	sleep(1);
    kill(childPid, g_childSignal);
    
    while(1)
    {
    	pause();
    } 
}

static void ChildFunction()
{
	SetSignal(g_childSignal, SignalHandlerChild);
	
	while(1)
    {
    	pause();
    	printf("process: %d sent signal: %d to parent", getpid(), g_childSignal);
    } 
}

int main(int argc, char *argv[])
{
	extern char *optarg;
	int pid, opt;
	
	/*read input*/
	while ((opt = getopt(argc, argv, "p:c:s:")) != -1)
	{
		switch(opt)
		{
			case 'p':
				g_parentSignal = atoi(optarg);
				break;
			case 'c':
				g_childSignal = atoi(optarg);
				break;
			case 's':
				g_time = atoi(optarg);
				break;
	 	}
	}
	
	/*make new process and run it*/
	pid = fork();
	if(pid < 0)
	{
		perror("fork");
	}
	else if(pid > 0)
	{
		ParentFunction(pid);
	}
	else
	{
		ChildFunction();
	}
	return 0;
}
