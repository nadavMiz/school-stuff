#include <iostream>
#include <string.h> //strlen for buffer size
#include <typeinfo>

#include "virtIO.h"
#include "asciiIO.h"
#include "binIO.h"

using namespace std;


int main()
{
	static string errors[] = {"ok", "can't open file", "bad access", "write error", "read error"};
	biniIO_t* binaryFile;
	bool isRunning = true;
	int input;
	long longData;
	float floatData;
	char buffer[30];
	string mode, fileName;
	virtIO_t::status_e error;

	virtIO_t* myFile;
	
	cout << "which io would you like to use?" << endl;
	cout << "1) ascii" << endl;
	cout << "2) binary" << endl;
	cin >> input;
	
	switch(input)
	{
		case 1:
			myFile = new asciiIO_t();
			break;
			
		case 2:
			myFile = new biniIO_t();
			break;
		
		default:
			return 0;
	}
	
	while(isRunning)
	{
		cout << "what would you like to do?" << endl;
		cout << "1) open file" << endl;
		cout << "2) close file" << endl;
		cout << "3) write long" << endl;
		cout << "4) write float" << endl;
		cout << "5) read long" << endl;
		cout << "6) read float" << endl;
		cout << "7) get length" << endl;
		cout << "8) get status" << endl;
		cout << "9) get access" << endl;
		cout << "10) get path" << endl;
		cout << "11) get position" << endl;
		cout << "12) set position" << endl;
		cout << "13) write to buffer (binary only)" << endl;
		cout << "14) read from buffer (binary only)" << endl;
		cout << "any other number - quit" << endl;
		
		cin >> input;
		
		switch (input)
		{
			case 1:
				cout << "how would you like to call the file?" << endl;
				cin >> fileName;
				cout << "how would you like to open the file?" << endl;
				cin >> mode;
				myFile->Open(fileName, mode);
				break;
			
			case 2:
				myFile->close();
				break;
				
			case 3:
				cout << "enter long to write" << endl;
				cin >> longData;
				
				try
				{
					*myFile << longData;
				}
				catch(virtIO_t::status_e _e)
				{
					cout << "had problem: " << _e << endl;
				}
				break;
				
			case 4:
				cout << "enter float to write" << endl;
				cin >> floatData;
				
				try
				{
					*myFile << floatData;
				}
				catch(virtIO_t::status_e _e)
				{
					cout << "had problem: " << _e << endl;
				}
				break;
				
			case 5:
				try
				{
					*myFile >> longData;
					cout << longData << endl;
				}
				catch(virtIO_t::status_e _e)
				{
					cout << "had problem: " << _e << endl;
				}
				break;
				
			case 6:
				try
				{
					*myFile >> floatData;
					cout << floatData << endl;
				}
				catch(virtIO_t::status_e _e)
				{
					cout << "had problem: " << _e << endl;
				}
				break;
				
			case 7:
				cout << myFile->Length() << endl;
				break;
				
			case 8:
				cout << myFile->GetStatus() << endl;
				break;
				
			case 9:
				cout << myFile->GetAccess() << endl;
				break;
				
			case 10:
				cout << myFile->GetPath() << endl;
				break;
				
			case 11:
				cout << myFile->GetPosition() << endl;
				break;
				
			case 12:
				cout << "enter new position" << endl;
				
				cin >> longData;
				error = myFile->SetPosition(longData);
				
				if(virtIO_t::ok_e != error)
				{
					cout << "error accured: " << error << endl;
				}
				break;
				
			case 13:
				binaryFile = dynamic_cast<biniIO_t*>(myFile);
				if(0 == binaryFile)
				{
					break;
				}
			
				cout << "how much would you like to read" << endl;
				cin >> input;
				
				try
				{
					*binaryFile >> (void*)buffer, input;
					cout << buffer << endl;
				}
				catch(virtIO_t::status_e _e)
				{
					cout << "had problem: " << _e << endl;
				}
				break;
				
			case 14:
				binaryFile = dynamic_cast<biniIO_t*>(myFile);
				if(0 == binaryFile)
				{
					break;
				}
			
				cout << "what would you like to write" << endl;
				cin >> buffer;
				
				try
				{
					*binaryFile << (void*)buffer, strlen(buffer);
				}
				catch(virtIO_t::status_e _e)
				{
					cout << "had problem: " << _e << endl;
				}
				break;
			
			default:
				isRunning = false;
				break;
		}
		
	}
	
	return 1;
}
