#ifndef __BITS_H__
#define __BITS_H__

typedef struct
{
	unsigned char m_ink: 4;
	unsigned char  : 1;
	unsigned char m_isJamed: 1;
	unsigned char m_isEmpty: 1;
	unsigned char m_isStandby: 1;
} StatusStruct;

typedef union
{
	StatusStruct statusStruct;
	char statusByte;
} PrinterStatusUnion;


/*prints the size of an unpacked struct and a packed one*/
void PackOnStruct();

/*prints a decimal number in hexadecimal digits*/
void DecToHex(int _num);

/*returns the abselute value of the number*/
int ABS(int _num);

/*prints the printer status*/
void PrinterStatus(PrinterStatusUnion _status);

#endif 
