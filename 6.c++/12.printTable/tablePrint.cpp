
#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <string>

using namespace std;

const unsigned int LINE_LENGTH = 30;

ostream& PrintLine(ofstream& _os)
{
	_os << '|' << setw(LINE_LENGTH - 2) << setfill('-') << right << '|' << endl;
	
	return _os << setfill(' ');
}

ostream& PrintTableLine(ofstream& _os, const string& _name, unsigned int _age)
{
	return _os << '|' << setw(3) << left << _age << '|'
		 << setw(LINE_LENGTH - 7) << setfill('.') << left << _name << '|' << endl;
}

void GetInput(string& _name, unsigned int& _age)
{
	cout << "enter name and id" << endl;
	
	cin >> _name >> _age;
}

void PrintTable(ofstream& _os)
{
	string name1, name2;
	unsigned int age1, age2;

	GetInput(name1, age1);
	GetInput(name2, age2);
	
	PrintLine(_os);
	PrintTableLine(_os, name1, age1);
	PrintLine(_os);
	PrintTableLine(_os, name2, age2);
	PrintLine(_os);
}

int main()
{
	
	ofstream outFile;
	
	outFile.open("Table");
	
	PrintTable(outFile);
	
	outFile.close();
	
	return 1;
}
