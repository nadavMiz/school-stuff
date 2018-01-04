#ifndef __PERSONAL_ACOUNT_H__
#define __PERSONAL_ACOUNT_H__

#include <iostream>

#include "acountImp.h"

using namespace std;

class Subject;

class PersonalAcount: public AcountImp
{
	public:
		PersonalAcount(){}
		virtual ~PersonalAcount(){}
		
		virtual void Update(const Subject* ChngSubject) {cout << "invetation was recived" << endl; }
};

#endif /* __PERSONAL_ACOUNT_H__ */

