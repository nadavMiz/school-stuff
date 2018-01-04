#include <iostream>
#include <string.h>

#include "memPage_t.h"
#include "memPool_t.h"

using namespace std;

int main()
{
	int input, position, size;
	bool isRunning = true;
	char* inputData = new char[1024];
	char* outputData = new char[1024];
	MemPool_t memmory;

	while(isRunning)
	{
		cout << "what would you like to do?\n";
		cout << "1) write data at current position\n";
		cout << "2) write data at a given position\n";
		cout << "3) read data from current position\n";
		cout << "4) read data from a given position\n";
		cout << "5) change current position\n";
		cout << "6) get current position\n";
		cout << "7) get actual size\n";
		cout << "8) get default page capacity\n";
		cout << "9) set default page capacity\n";
		cout << "any other number - quit\n";
	
		cin >> input;
		
		switch(input)
		{
			case 1:
				cout << "what would you like to write?\n";	
				cin >> inputData;
				memmory.Write(inputData, strlen(inputData));
				break;
		
			case 2:
				cout << "what would you like to write?\n";	
				cin >> inputData;
				cout << "where would you like to write?\n";
				cin >> position;
				memmory.Write(inputData, strlen(inputData), position);
				break;
		
			case 3:
				cout << "how much would you like to read?\n";
				cin >> size;
				memmory.Read(outputData, size);
				cout << "data is: " << outputData << endl;
				break;
		
			case 4:
				cout << "how much would you like to read?\n";
				cin >> size;
				cout << "where would you like to read from?\n";
				cin >> position;
				memmory.Read(outputData, size, position);
				cout << "data is: " << outputData << endl;
				break;
		
			case 5:
				cout << "where would you like to change the position to?\n";
				cin >> position;
				try
				{
					memmory.SetCurrentPosition(position);
				}
				catch(unsigned int _pos)
				{
					cout << "invalid position: " << _pos << endl;
				}
				break;
				
			case 6:
				cout << "current position is: " << memmory.GetCurrentPosition() << endl;
				break;
				
			case 7:
				cout << memmory.GetActualSize() << endl;
				break;
				
			case 8:
				cout << memmory.GetDefaultPageCapacity() << endl;
				break;
				
			case 9:				
				cout << "what default capacity would you like to have?'\n";
				cin >> size;
				memmory.SetDefaultPageCapacity(size);
				break;
		
			default:
				isRunning = false;
				break; 
		}
	}
}
