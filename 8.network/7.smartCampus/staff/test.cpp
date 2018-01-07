#include <iostream>
#include <sstream>
#include <string>

#include "multiKeySearchTree.h"

using namespace std;

int main()
{
	smartCampus::MultiKeySearchTree<int> tree;
	
	stringstream ss("fire 1");
	stringstream ss1("fire 6");
	stringstream ss2("fire 5");
	stringstream ss3("fire 1");
	stringstream ss4("fire 1");
	stringstream ss5("dog 1");
	stringstream ss6("dog 5");
	
	//tree.Insert(stringstream("fire 1"), 5);
	//tree.Insert(ss, 5);
	
	return 1;
}
