#ifndef __BOOK_H__
#define __BOOK_H__

#include <string>

using namespace std;


class book_t
{
	public:
		book_t(const string& _isbn, const string& _title, const string& _author, const string& _subject);
		virtual ~book_t ();

		const string& GetTitle() const;
		const string& GetAuthor() const;
		const string& GetIsbn() const;

	private:
		/* data */
		string m_title;
		string m_author;
		string m_subject;
		string m_isbn; //book id
};

#endif /* __BOOK_H__ */

