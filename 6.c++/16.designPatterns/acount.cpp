#include "observer.h"
#include "acount.h"
#include "acountFactory.h"
#include "acountImp.h"

Acount::Acount(const string& _type, Subject* _subject): Observer(_subject, _type)
{
	m_acount = AcountFactory::CreateAcount(_type);	
	if(0 == m_acount)
	{
		throw "bad account";
	}
}

Acount::~Acount()
{
	delete m_acount;
}

void Acount::Update(const Subject* ChngSubject)
{
	if(0 != m_acount)
	{ 
		m_acount->Update(ChngSubject);
	}
}
