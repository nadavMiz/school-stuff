#ifndef __FAMILY_ACOUNT_H__
#define __FAMILY_ACOUNT_H__

#include <iostream>

#include "acountImp.h"

using namespace std;

class Subject;

class FamilyAcount: public AcountImp
{
	public:
		FamilyAcount(){};
		virtual ~FamilyAcount(){};
		
		virtual void Update(const Subject* ChngSubject){cout << "got the bonus" << endl; }

};

#endif /* __FAMILY_ACOUNT_H__ */

