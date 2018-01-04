#ifndef __ACOUNT_FACTORY_H__
#define __ACOUNT_FACTORY_H__

#include <string>

class AcountImp;

using namespace std;

class AcountFactory 
{
	public:

		static AcountImp* CreateAcount(const string& Impl);
	
	private:
		~AcountFactory();
		AcountFactory();
};

#endif /* __ACOUNT_FACTORY_H__ */

