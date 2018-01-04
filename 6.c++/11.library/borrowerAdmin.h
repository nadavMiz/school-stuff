#ifndef __BORROWER_ADMIN_H__
#define __BORROWER_ADMIN_H__

#include <string>
#include <iostream>
#include <list>
#include <map>

#include "borrowerRecord.h"
#include "borrower.h"
#include "book.h"

using namespace std;

class borrowerAdmin_t
{
	public:
		borrowerAdmin_t();
		virtual ~borrowerAdmin_t ();

		virtual bool AddBorrower(const string& _name, const string& _adress, const string& _phoneNumber);
		virtual bool RemoveBorrower(const borrowerRecord_t* _borrower);
		
		virtual bool BorrowBook(const borrowerRecord_t* _borrower, const book_t* _book);
		virtual bool ReturnBook(const borrowerRecord_t* _borrower, const book_t* _book);
		
		virtual const borrowerRecord_t* FindById(unsigned int _id) const;
		virtual const List<borrowerRecord_t*> FindByName(const string& _name) const;
		
		virtual void ReportBorrower(ostream& _os, unsigned int _id) const;
		virtual void ReportAllBorrowers(ostream& _os) const;
		
		

	private:
		/* data */
		map<string, borrowerRecord_t*> m_borrowerRecords;
};

#endif /* __BORROWER_ADMIN_H__ */

