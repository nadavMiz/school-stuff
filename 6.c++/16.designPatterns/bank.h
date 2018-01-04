#ifndef __BANK_H__
#define __BANK_H__

#include <vector>
#include <string>

#include "subject.h"

using namespace std;

class Acount;

class Bank: Subject
{ 
	public: 
		static Bank& createObj() {return m_bank;}
		bool CreateAcount(const string& _type);
		void GiveBonus() const;
		void SendInvitations() const;
		void InvestMoney() const;
	
	
	protected: 
		// multimap<string, Observer*> m_observers;
		
		// virtual void Notify(const string& _type) const;
		~Bank();
		 
	private: 
		static Bank m_bank;
		 
	private: 
		Bank(){};
		Bank(const Bank&);
		void operator=(Bank&);
}; 

#endif /* __BANK_H__ */

