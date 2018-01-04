#include <iostream>
#include <vector>       
#include <list>  
//
#include "tContainer.h"
#include "tContainer2.h"

using namespace std;

int main()
{
	int input, data;
	int *output;
	bool isRunning = true;
	int constainerType;
	
	tContainer2_t<int, vector> myVector;
	tContainer2_t<int, list> myList;
	
	cout << "what kind of container would you like to use?\n";
	cout << "1) vector\n";
	cout << "2) list\n";
	
	cin >> constainerType;
	
	while(isRunning)
	{
		cout << "what would you like to do?\n";
		cout << "1) add item\n";
		cout << "2) get first\n";
		cout << "3) get last\n";
		cout << "4) get at index([])\n";
		cout << "5) find\n";
		cout << "6) get size\n";
		cout << "7) is empty\n";
		cout << "8) remove\n";
		cout << "9) remove and delete all\n";
		cout << "any other number - quit\n";
		
		cin >> input;
		
		switch(input)
		{
			case 1:
				cout << "what would you like to add?\n";
				cin >> data;
				
				if(1 == constainerType)
				{
					myVector.PushBack(new int(data));
				}
				else
				{
					myList.PushBack(new int(data));
				}
				break;
				
			case 2:
				if(1 == constainerType)
				{
					output = myVector.GetFirstElem();
				}
				else
				{
					output = myList.GetFirstElem();
				}
				if(output == 0)
				{
					cout << "invalid val\n";
				}
				else
				{
					cout << "data is: " << *output << endl;
				}
				break;
				
			case 3:
				if(1 == constainerType)
				{
					output = myVector.GetLastElem();
				}
				else
				{
					output = myList.GetLastElem();
				}
				
				if(output == 0)
				{
					cout << "invalid val\n";
				}
				else
				{
					cout << "data is: " << *output << endl;
				}
				break;
				
			case 4:
				cout << "please enter index\n";
				cin >> data;
			
				if(1 == constainerType)
				{
					output = myVector[data];
				}
				else
				{
					output = myList[data];
				}
				
				if(output == 0)
				{
					cout << "invalid val\n";
				}
				else
				{
					cout << "data is: " << *output << endl;
				}
				
				break;
			
			case 5:
				cout << "what would you like to find?\n";
				cin >> data;
				
				if(1 == constainerType)
				{
					output = myVector.Find(data);
				}
				else
				{
					output = myList.Find(data);
				}
				
				if(output == 0)
				{
					cout << "invalid val\n";
				}
				else
				{
					cout << "data is: " << *output << endl;
				}
				
				break;
			
			case 6:
				if(1 == constainerType)
				{
					data = myVector.Size();
				}
				else
				{
					data = myList.Size();
				}
				
				cout << "data is: " << data << endl;
				
				break;
				
			case 7:
				if(1 == constainerType)
				{
					data = myVector.IsEmpty();
				}
				else
				{
					data = myList.IsEmpty();
				}
				
				cout << "data is: " << data << endl;
				
				break;
				
			case 8:
				cout << "what would you like to remove?\n";
				cin >> data;
				
				if(1 == constainerType)
				{
					output = myVector.Remove(data);
				}
				else
				{
					output = myList.Remove(data);
				}
				
				if(output == 0)
				{
					cout << "invalid val\n";
				}
				else
				{
					cout << "data is: " << *output << endl;
					delete output;
				}
				
				break;
				
			case 9:
				if(1 == constainerType)
				{
					myVector.RemoveAndDeleteAll();
				}
				else
				{
					myList.RemoveAndDeleteAll();
				}
				break;
			
			default:
				isRunning = false;
				break;
				
		}
		
	}
	
	return 1;
}
