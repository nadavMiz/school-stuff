#ifndef __BOOK_ADMIN_H__
#define __BOOK_ADMIN_H__

#include <string>
#include <iostream>
#include <list>
#include <map>

#include "bookRecord.h"
#include "book.h"
#include "borrower.h"

using namespace std;

class bookAdmin_t
{
	public:
		bookAdmin_t();
		virtual ~bookAdmin_t();
		
		bool IsBookAvailable(const string& _isbn) const;

		virtual bool AddBook(const string& _isbn, const string& _title, const string& _author, const string& _subject);
		virtual bool RemoveBook(const bookRecord_t* _book);
		
		virtual bool BorrowBook(const bookRecord_t* _book, const borrower_t* _borrower);
		virtual bool ReturnBook(const bookRecord_t* _book, const borrower_t* _borrower);

		virtual const list<bookRecord_t*> FindByName(const string& _bookName) const;
		virtual const list<bookRecord_t*> FindByAuthor(const string& _author) const;
		virtual const list<bookRecord_t*> FindBySubject(const string& _subject) const;
		virtual const bookRecord_t*       FindByIsbn(const string& _isbn) const;

		virtual ostream& ReportBook(ostream& _os, const string& _isbn) const;
		virtual ostream& ReportAllBooks(ostream& _os) const;



	private:
		/* data */
		map<string, bookRecord_t*> m_bookRecords;
};

#endif /* __BOOK_ADMIN_H__ */

