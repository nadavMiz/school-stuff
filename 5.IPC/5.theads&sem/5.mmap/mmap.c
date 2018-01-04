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
	
	sharedMem = mmap(NULL, 23*sizeof(char), PROT_READ, MAP_SHARED, myfile, 0);
	offset = atoi(sharedMem);
	readNum = atoi(sharedMem + offset);
	write(0, sharedMem + 3, readNum);
	printf("\n");
	
	close(myfile);
}
