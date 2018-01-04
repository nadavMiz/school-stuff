#ifndef __BOOK_RECORD_H__
#define __BOOK_RECORD_H__

#include <iostream>
#include <string>
#include <list>

#include "book.h"
#include "borrower.h"

using namespace std;

class bookRecord_t
{
	public:
		bookRecord_t(const book_t* _book);
		virtual ~bookRecord_t ();

		const book_t* GetBook() const;
		const borrower_t* GetBorrower() const;
		
		virtual bool AddBorrower(const borrower_t* _borrower);
		virtual bool RemoveBorrower(const borrower_t* _borrower);
		
		friend ostream& operator<<(ostream& _os, const bookRecord_t& _book); //calls print function
	
		
	protected:
		virtual ostream& Print(ostream& _os) const;

	private:
		/* data */
		book_t* m_book;
		borrower_t* m_borrower;
};

#endif /* __BOOK_RECORD_H__ */

