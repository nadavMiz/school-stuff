#ifndef __BORROWER_RECORD_H__
#define __BORROWER_RECORD_H__

#include <list>

#include "borrower.h"
#include "book.h"

class borrowerRecord_t
{
	public:
		borrowerRecord_t (Borrower_t* _newBorrower);
		virtual ~borrowerRecord_t ();
		
		const borrower* GetBorrower() const;
		const List<book_t*> GetBorrowedBooks() const;
		
		virtual bool BorrowBook(const book_t* _book);
		virtual bool ReturnBook(const book_t* _book);
		
		friend ostream& operator<<(ostream& _os, const borrowerRecord_t& _book); //calls print function
	
	protected:
		virtual ostream& Print(ostream& _os) const;
	
	private:
		/* data */
		borrower_t* m_borrower;
		List<const book_t*> m_currentlyBorrowed;
		
		/* static data */
		static unsigned int m_numBorrowers;
};

#endif /* __BORROWER_RECORD_H__ */

