#ifndef __VIR_IO_H__
#define __VIR_IO_H__

#include <stdio.h>
#include <string>

using namespace std;

class virtIO_t
{
	public:
		enum status_e
		{
			ok_e = 0,
			cant_open_file_e,
			bad_access_e,
			writeErr_e,
			readErr_e
		};
		
	public:
		virtIO_t();
		virtIO_t(const string& _path, const string& _mode);
		virtual ~virtIO_t();
		
		status_e Open(const string& _name, const string& _mode);
		status_e Open();
		
		void close();
		
		long int Length() const;
		const string& GetPath() const {return m_path;}
		const string& GetAccess() const {return m_access;}
		status_e GetStatus() const {return m_status;}
		long int GetPosition() const {return ((0 != m_file) ? ftell(m_file): 0);}
		bool IsFileOpen() const { return (0 != m_file);}
		status_e SetPosition(long int _position);
		
		virtual char& operator>>(char& _data) = 0;
		virtual unsigned char& operator>>(unsigned char& _data) = 0;
		virtual short& operator>>(short& _data) = 0;
		virtual unsigned short& operator>>(unsigned short& _data) = 0;
		virtual int& operator>>(int& _data) = 0;
		virtual unsigned int& operator>>(unsigned int& _data) = 0;
		virtual long& operator>>(long& _data) = 0;
		virtual unsigned long& operator>>(unsigned long& _data) = 0;
		virtual float& operator>>(float& _data) = 0;
		virtual double& operator>>(double& _data) = 0;
		
		virtual virtIO_t& operator<<(char _data) = 0;
		virtual virtIO_t& operator<<(unsigned char _data) = 0;
		virtual virtIO_t& operator<<(short _data) = 0;
		virtual virtIO_t& operator<<(unsigned short _data) = 0;
		virtual virtIO_t& operator<<(int _data) = 0;
		virtual virtIO_t& operator<<(unsigned int _data) = 0;
		virtual virtIO_t& operator<<(long _data) = 0;
		virtual virtIO_t& operator<<(unsigned long _data) = 0;
		virtual virtIO_t& operator<<(float _data) = 0;
		virtual virtIO_t& operator<<(double _data) = 0;

	protected:
		/* data */
		FILE* m_file;
		
		/* static data */
		static string m_modeTable[];
		
	protected:
		void SetStatus(status_e _status) {m_status = _status;}
		bool IsValidMode(const string& _mode) const;
		bool IsWriteable() const { return ((m_access != "r") && (m_access != "")); }
		bool IsReadable() const{ return ((m_access != "a") && (m_access != "w") && (m_access != "")); }
		
		
	private:
		/* data */
		string m_path;
		string m_access;
		status_e m_status;
		
	private:
		virtIO_t(const virtIO_t& _virIO);
		virtIO_t& operator=(const virtIO_t& _virIO);
		
		status_e OpenFile();
};

#endif /* __VIR_IO_H__ */

