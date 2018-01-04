#include <string>

#include "acountFactory.h"
#include "acountImp.h" 
#include "personalAcount.h"
#include "familyAcount.h"
#include "stockAcount.h"

AcountImp* AcountFactory::CreateAcount(const string& _type)
{
	if(_type == "personal")
	{
		return new PersonalAcount();
	} 
	else if(_type == "family")
	{
		return new FamilyAcount();
	}
	else if(_type == "stock")
	{
		return new StockAcount();
	}
	
	return 0;
}
