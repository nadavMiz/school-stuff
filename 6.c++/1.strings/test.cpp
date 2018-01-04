#include <iostream>

#include "strings.h"

#define INPUT_SIZE 128
#define TRUE 1;

using namespace std;

int main()
{
	String_t str1;
	String_t str2;
	
	int input, index;
	int isRunning = 1;
	char inputString[INPUT_SIZE];
	
	while(isRunning)
	{
		cout << "\nwhat would you like to do\n";
		cout << "1) print string 1\n";
		cout << "2) print string 2\n";
		cout << "3) set string 1\n";
		cout << "4) set string 2\n";
		cout << "5) convert to upper\n";
		cout << "6) convert to lower\n";
		cout << "7) prepend from string 2\n";
		cout << "8) prepend from char*\n";
		cout << "9) string 1 += string 2\n";
		cout << "10) string 1 += input string\n";
		cout << "11) string 1 != string 2\n";
		cout << "12) string 1 != input string\n";
		cout << "13) string 1 < string 2\n";
		cout << "14) string 1 < input string\n";
		cout << "15) check if string 1 contains string 2\n";
		cout << "16) get charecter at index\n";
		cout << "17) cout << string 1\n";
		cout << "18) cin >> string 1\n";
		cout << "any other number - quit\n";
	
		cin >> input;
	
		switch(input)
		{
			case 1:
				str1.Print();
				break;
			
			case 2:
				str2.Print();
				break;
			
			case 3:
				cout << "please enter string to set\n";
				cin >> inputString;
				str1.SetString(inputString);
				break;
			
			case 4:
				cout << "please enter string to set\n";
				cin >> inputString;
				str2.SetString(inputString);
				break;
				
			case 5:
				str1.ConvertToUpper();
				break;
				
			case 6:
				str1.ConvertToLower();
				break;
				
			case 7:
				str1.Prepend(str2);
				break;
				
			case 8:
				cout << "please enter string prepend\n";
				cin >> inputString;
				str1.Prepend(inputString);
				break;
				
			case 9:
				str1 += str2;
				break;
				
			case 10:
				cout << "please enter string\n";
				cin >> inputString;
				str1 += inputString;
				break;
			
			case 11:
				cout << (str1 != str2) << "\n";
				break;
			
			case 12:
				cout << "please enter string\n";
				cin >> inputString;
				cout << (str1 != inputString) << "\n";
				break;
			
			case 13:
				cout << (str1 < str2) << "\n";
				break;
				
			case 14:
				cout << "please enter string prepend\n";
				cin >> inputString;
				cout << (str1 < inputString) << "\n";
				break;
			
			case 15:
				cout << str1.Contains(str2) << "\n";
				break;
				
			case 16:
				cout << "please enter index\n";
				cin >> index;
				cout << str1[index] << "\n";
				break;
			
			case 17:
				cout << str1;
				break;
			
			case 18:
				cin >> str1;
				break;
			
			default:
				isRunning = 0;
				break;
		}	
	}
}
