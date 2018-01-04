#include <stdio.h>
#include <string.h>

int main()
{
	FILE* myfile = NULL;
	char name[128];
	int age;
	int
	myfile = fopen("names.txt", "w");
	printf("enter name\n");
	fgets(name, 128, stdin);
	fwrite(name, sizeof(char), strlen(name), myfile);
	printf("enter age\n");
	scanf("%d" , &age);
	getchar();
	fwrite(&age, sizeof(int), 1, myfile);
	fclose(myfile);
	myfile = fopen("names.txt", "r");
	
}
