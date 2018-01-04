#ifndef __ASCII_IO_H__
#define __ASCII_IO_H__

#include "virtIO.h"

class asciiIO_t: public virtIO_t
{
	public:
		asciiIO_t(){};
		asciiIO_t(const string& _path, const string& _mode): virtIO_t(_path, _mode){}
		virtual ~asciiIO_t(){};
		
		//status_e Open(const string& _name, string _mode);
		//status_e Open();
		
		//void close();
		
		//long int Length() const;
		//const string& GetPath() const {return m_path;}
		//const string& GetAccess() const {return m_access;}
		//status_e GetStatus() const {return m_status;}
		//long int GetPosition() const {return ((0 != m_file) ? ftell(m_file): 0);}
		//status_e SetPosition(long int _position);
		
		
		/*************************************************
			all >> & << operators throw status_e exception
		**************************************************/
		virtual char& operator>>(char& _data) { return Read(_data, "%c ");}
		virtual unsigned char& operator>>(unsigned char& _data) { return Read(_data, "%hhu ");}
		virtual short& operator>>(short& _data) { return Read(_data, "%hd ");}
		virtual unsigned short& operator>>(unsigned short& _data) { return Read(_data, "%hu ");}
		virtual int& operator>>(int& _data) { return Read(_data, "%d ");}
		virtual unsigned int& operator>>(unsigned int& _data) { return Read(_data, "%u ");}
		virtual long& operator>>(long& _data) { return Read(_data, "%ld ");}
		virtual unsigned long& operator>>(unsigned long& _data) { return Read(_data, "%lu ");}
		virtual float& operator>>(float& _data) { return Read(_data, "%f ");}
		virtual double& operator>>(double& _data) { return Read(_data, "%lf ");}
		
		virtual asciiIO_t& operator<<(char _data) { return Write(_data, "%c ");}
		virtual asciiIO_t& operator<<(unsigned char _data) { return Write(_data, "%hhu ");}
		virtual asciiIO_t& operator<<(short _data) { return Write(_data, "%hd ");}
		virtual asciiIO_t& operator<<(unsigned short _data) { return Write(_data, "%hu ");}
		virtual asciiIO_t& operator<<(int _data) { return Write(_data, "%d ");}
		virtual asciiIO_t& operator<<(unsigned int _data) { return Write(_data, "%u ");}
		virtual asciiIO_t& operator<<(long _data) { return Write(_data, "%ld ");}
		virtual asciiIO_t& operator<<(unsigned long _data) { return Write(_data, "%lu ");}
		virtual asciiIO_t& operator<<(float _data) { return Write(_data, "%f ");}
		virtual asciiIO_t& operator<<(double _data) { return Write(_data, "%lf ");}

	//protected:
		/* data */
		//FILE* m_file;
		
		/* static data */
		//static string m_modeTable[];
		
	//protected:
		//void SetStatus(status_e _status) {m_status = _status;}
		//bool IsValidMode(const string& _mode) const;
		
	private:
		template<class T>
		T& Read(T& _data, const char* _format);
		template<class T>
		asciiIO_t& Write(const T& _data, const char* _format);
};

template<class T>
T& asciiIO_t::Read(T& _data, const char* _format)
{
	if(0 == m_file)
	{
		SetStatus(cant_open_file_e);
		throw cant_open_file_e;
	}
	
	if(!IsReadable())
	{
		SetStatus(bad_access_e);
		throw bad_access_e;
	}
	
	if(fscanf(m_file, _format, &_data) == EOF)
	{
		SetStatus(writeErr_e);
		throw writeErr_e;
	}
	
	SetStatus(ok_e);
	return _data;
}

template<class T>
asciiIO_t& asciiIO_t::Write(const T& _data, const char* _format)
{
	if(0 == m_file)
	{
		SetStatus(cant_open_file_e);
		throw cant_open_file_e;
	}
	
	if(!IsWriteable())
	{
		SetStatus(bad_access_e);
		throw bad_access_e;
	}
	
	if(fprintf(m_file, _format, _data) < 0)
	{
		SetStatus(readErr_e);
		throw readErr_e;
	}
	
	SetStatus(ok_e);
	return *this;
}

#endif /* __ASCII_IO_H__ */

