#ifndef __BORROWER_H__
#define __BORROWER_H__

#include <string>

using namespace std;


class borrower_t
{
	public:
		borrower_t();
		virtual ~borrower_t ();
		
		const string& GetName() const;
		const string& GetPhoneNumber() const;
		unsigned int GetID() const;
		
		void SetPhoneNumber(const string& _newName);
		void SetPhoneNumber(const char* _newNumber);

	private:
		/* data */
		string m_name;
		string m_phoneNumber;
		unsigned int m_id;
};

#endif /* __BORROWER_H__ */

