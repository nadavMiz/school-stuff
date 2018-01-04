#include "bank.h"
#include "acount.h"

Bank Bank::m_bank;

bool Bank::CreateAcount(const string& _type)
{	
	try
	{
		new Acount(_type, this);
	}	
	catch(const char* _err)
	{
		return false;
	}
	
	return true;
}

void Bank::GiveBonus() const
{
	Notify("family");
}

void Bank::SendInvitations() const
{
	Notify("personal");
}

void Bank::InvestMoney() const
{
	Notify("stock");
}

Bank::~Bank()
{
	for(multimap<string, Observer*>::iterator itr = m_observers.begin(); itr != m_observers.end(); ++itr)
	{
		delete itr->second;
	}
}
