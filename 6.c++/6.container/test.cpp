#include "container_t.h"
#include "vector_t.h"
#include "Dlist_t.h"

#include <iostream>

using namespace std;

int main()
{
	bool isRunning = true;
	int userInput, *intInput;
	char strInput[128];
	
	container_t<int>* container;

	cout << "what container would you like to use \n";
	cout << "1) vector\n";
	cout << "2) linked list\n";
	cin >> userInput;
	
	if(1 == userInput)
	{
		container = new Vector_t<int>;
	}
	else
	{
		container = new DList<int>;
	}
	
	
	while(isRunning)
	{
		cout << "what would you like to do?\n";
		cout << "1) append\n";
		cout << "2) prepend\n";
		cout << "3) insert\n";
		cout << "4) index\n";
		cout << "5) find\n";
		cout << "6) contains\n";
		cout << "7) remove\n";
		cout << "8) remove all\n";
		cout << "9) get size\n";
		cout << "10) is empty\n";
		cout << "any other number - quit\n";
		
		cin >> userInput;
		
		switch(userInput)
		{
			case 1:
				cout << "what would you like to add\n";
				intInput = new int;
				cin >> *intInput;
				cout << "where would you like to add it?\n";
				cin >> userInput;
				container->Append(userInput, intInput);
				break;
				
			case 2:
				cout << "what would you like to add\n";
				intInput = new int;
				cin >> *intInput;
				cout << "where would you like to add it?\n";
				cin >> userInput;
				container->Prepend(userInput, intInput);
				break;
				
			case 3:
				cout << "what would you like to add\n";
				intInput = new int;
				cin >> *intInput;
				container->Insert(intInput);
				break;
				
			case 4:
				cout << "what would you like to find\n";
				cin >> userInput;
				cout << "the index is: " << container->Index(userInput) << endl;
				break;
				
			case 5:
				cout << "what would you like to find\n";
				cin >> userInput;
				cout << "the item is: " << *(container->Find(userInput)) << endl;
				break;
				
			case 6:
				cout << "what would you like to find\n";
				cin >> userInput;
				cout << "result: " << container->Contains(userInput) << endl;
				break;
				
			case 7:
				cout << "what would you like to remove\n";
				cin >> userInput;
				cout << "result: " << container->RemoveAndDelete(userInput) << endl;
				break;
			
			case 8:
				container->RemoveAndDeleteAll();
				cout << "all was removed\n";
				break;
				
			case 9:
				cout << "size is: " << container->Count() << endl;
				break;
			
			case 10:
				cout << "container is: " << container->IsEmpty() << " empty\n";
				break;
			
			default:
				isRunning = false;
				break;
		}
	}
	return 1;
}
