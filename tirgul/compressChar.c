#include <stdio.h>
#include <string.h>
#include <limits.h>

unsigned char* StrCompress(unsigned char* _str)
{
	unsigned short charCopy, tmp = 0;
	unsigned int leftShift = 0;
	unsigned char* dest = _str;
	unsigned char* current = _str;
	
	while(*current != '\0')
	{
		charCopy = *current;
		tmp += charCopy << leftShift;
		
		leftShift += 5;
		if(leftShift > CHAR_BIT)
		{
			*dest |= (char)charCopy;
			tmp >> CHAR_BIT;
			++dest;
			leftShift -= CHAR_BIT;
		}
		
		++current;
	}
	
	dest[1] = tmp;
	if(tmp)
	{
		dest[2] = '\0';
	}
	
	return _str;
}

int main()
{
	unsigned char str[] = {30,22,21,22,10};
	printf("%d\n", StrCompress(str)[1]);
	return 0;
}
