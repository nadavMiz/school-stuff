#include <stdio.h>
#include <limits.h>
#include <string.h>

#include "bits.h"

#define BITS_IN_HEXA 4
#define MAX_HEXA_DIGIT 15
#define IS_NEGATIVE(N) ((N) & (1 << (BITS_IN_INT - 1)))
#define BITS_IN_INT sizeof(int) * 8

typedef struct
{
	char a;
	int b;
	char c;
	int d;
	
} StructToPack;


#pragma pack(push, 1)
typedef struct
{
	char a;
	int b;
	char c;
	int d;
	
} PackedStruct;
#pragma pack(pop)

typedef struct
{
	char a;
	int b;
	char c;
	int d;
	
} UnackedStruct;

void PackOnStruct()
{
	printf("size of packed struct: %d\n", sizeof(PackedStruct));
	printf("size of unpacked struct: %d\n", sizeof(UnackedStruct));
}

void DecToHex(int _num)
{
	int i;
	int hexaIdx = 0;
	
	static char bitsToHexaTable[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
	for(i = BITS_IN_INT - BITS_IN_HEXA; i >= 0; i = i - BITS_IN_HEXA)
	{
		hexaIdx = (_num & (MAX_HEXA_DIGIT << i)) >> i;
		printf("%c", bitsToHexaTable[hexaIdx]);
	}
	printf("\n");
}

int ABS(int _num)
{
	return IS_NEGATIVE(_num) ? (~_num + 1) : _num;
}

void PrinterStatus(PrinterStatusUnion _status)
{
	static char statusTable[16][30];
	static int isFirstTime = 1;
	if (isFirstTime)
	{
		strcpy(statusTable[0], "everything is OK :)");
		strcpy(statusTable[1], "BLACK is empty");
		strcpy(statusTable[2], "CYAN is empty");
		strcpy(statusTable[3], "BLACK and CYAN are empty");
		strcpy(statusTable[4], "MAGENTA is empty");
		strcpy(statusTable[5], "BLACK and MAGENTA are empty");
		strcpy(statusTable[6], "CYAN and MAGENTA are empty");
		strcpy(statusTable[7], "BLACK, CYAN and MAGENTA are empty");
		strcpy(statusTable[8], "YELLOW is empty");
		strcpy(statusTable[9], "BLACK and YELLOW are empty");
		strcpy(statusTable[10], "CYAN and YELLOW are empty");
		strcpy(statusTable[11], "BLACK, CYAN and YELLOW are empty");
		strcpy(statusTable[12], "MAGENTA and YELLOW are empty");
		strcpy(statusTable[13], "BLACK, MAGENTA and YELLOW are empty");
		strcpy(statusTable[14], "CYAN, MAGENTA and YELLOW are empty");
		strcpy(statusTable[15], "BLACK, CYAN, MAGENTA and YELLOW are empty");
		isFirstTime = 0;
	}
	
	if(_status.statusStruct.m_isJamed)
	{
		printf("paper jam\n");
		return;
	}
	
	if(_status.statusStruct.m_isEmpty)
	{
		printf("there is no paper\n");
		return;
	}
	
	if(_status.statusStruct.m_isStandby)
	{
		printf("printer in standby\n");
		return;
	}
	printf("%s\n", statusTable[_status.statusStruct.m_ink]);
}


