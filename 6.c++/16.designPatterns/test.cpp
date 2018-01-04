#include <iostream>

#include "bank.h"

using namespace std;

int main()
{
	bool isRunning = true;
	int input;
	unsigned int amount;
	Bank& bank = Bank::createObj();
	
	while(isRunning)
	{
		cout << "what would you like to do" << endl;
		cout << "1) add personal saving acount" << endl;
		cout << "2) add family acount" << endl;
		cout << "3) add stock exchange acount" << endl;
		cout << "4) send invetations" << endl;
		cout << "5) give bonuses" << endl;
		cout << "6) invest money" << endl;
		cout << "any other number" << endl;
		
		cin >> input;
		
		switch(input)
		{
			case 1:
				cout << "how much would you like to add" << endl;
				cin >>  amount;
				
				for(unsigned int i = 0; i < amount; ++i)
				{
					bank.CreateAcount("personal");
				}
				break;
				
			case 2:
				cout << "how much would you like to add" << endl;
				cin >>  amount;
				
				for(unsigned int i = 0; i < amount; ++i)
				{
					bank.CreateAcount("family");
				}
				break;
				
			case 3:
				cout << "how much would you like to add" << endl;
				cin >>  amount;
				
				for(unsigned int i = 0; i < amount; ++i)
				{
					bank.CreateAcount("stock");
				}
				break;
				
			case 4:
				bank.SendInvitations();
				break;
				
			case 5:
				bank.GiveBonus();
				break;
				
			case 6:
				bank.InvestMoney();
				break;
				
			default:
				isRunning = false;
				break;
		}
	}
	
	return 1;
}
