#ifndef __STOCK_ACOUNT_H__
#define __STOCK_ACOUNT_H__

#include <iostream>

#include "acountImp.h"

using namespace std;

class Subject;

class StockAcount: public AcountImp
{
	public:
		StockAcount(){};
		virtual ~StockAcount (){};

		virtual void Update(const Subject* ChngSubject){cout << "money was invested" << endl; }

};

#endif /* __STOCK_ACOUNT_H__ */

