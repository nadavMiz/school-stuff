#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

int main()
{
	char* sharedMem;
	int offset, readNum;
	int myfile = open("nadav", O_RDWR);
	
	sharedMem = mmap(NULL, 30*sizeof(char), PROT_WRITE, MAP_SHARED, myfile, 0);
	(int)sharedMem = 24;
	strcpy((char*)sharedMem + sizeof(int), "nadav is da best!!!");
	(int)((char*)sharedMem + 24) = 5;
	
	close(myfile);
}
