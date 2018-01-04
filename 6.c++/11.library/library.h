#ifndef __LIBRARY_H__
#define __LIBRARY_H__

#include <string>
#include <iostream>

#include "bookAdmin.h"
#include "bookRecord.h"
#include "borrowerAdmin.h"
#include "borrowerRecord.h"

using namespace std;

class library_t
{
	public:
		library_t();
		virtual ~library_t ();
		
		bool AddBorrower(const string& _name, const string& _adress, const string& _phoneNumber);
		bool RemoveBorrower(const borrowerRecord_t* _borrower);
		
		bool AddBook(const string& _isbn, const string& _title, const string& _author, const string& _subject);
		bool RemoveBook(const bookRecord_t* _book);
		
		const borrowerAdmin_t* GetBorrowerAdmin() const;
		const bookAdmin_t* GetBookAdmin() const;
		
		virtual bool BorrowBook(const bookRecord_t* _book, const borrowerRecord_t* _borrower);
		virtual bool ReturnBook(const string& _bookIsbn, unsigned int _borrowerId);

	private:
		/* data */
		borrowerAdmin_t* m_borrowerAdmin;
		bookAdmin_t*     m_bookAdmin;
};

#endif /* __LIBRARY_H__ */

