#ifndef __BINI_IO_H__
#define __BINI_IO_H__

#include "virtIO.h"

class biniIO_t: public virtIO_t
{
	public:
		biniIO_t (){};
		biniIO_t(const string& _path, const string& _mode): virtIO_t(_path, _mode){};
		virtual ~biniIO_t (){};
		
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
		virtual char& operator>>(char& _data) { return *(Read(&_data));}
		virtual unsigned char& operator>>(unsigned char& _data){ return *(Read(&_data));}
		virtual short& operator>>(short& _data) { return *(Read(&_data));}
		virtual unsigned short& operator>>(unsigned short& _data){ return *(Read(&_data));}
		virtual int& operator>>(int& _data) { return *(Read(&_data));}
		virtual unsigned int& operator>>(unsigned int& _data) { return *(Read(&_data));}
		virtual long& operator>>(long& _data) { return *(Read(&_data));}
		virtual unsigned long& operator>>(unsigned long& _data){ return *(Read(&_data));}
		virtual float& operator>>(float& _data) { return *(Read(&_data));}
		virtual double& operator>>(double& _data) { return *(Read(&_data));}
		
		virtual biniIO_t& operator<<(char _data) { return Write(&_data); }
		virtual biniIO_t& operator<<(unsigned char _data) { return Write(&_data); }
		virtual biniIO_t& operator<<(short _data) { return Write(&_data); }
		virtual biniIO_t& operator<<(unsigned short _data) { return Write(&_data); }
		virtual biniIO_t& operator<<(int _data) { return Write(&_data); }
		virtual biniIO_t& operator<<(unsigned int _data) { return Write(&_data); }
		virtual biniIO_t& operator<<(long _data) { return Write(&_data); }
		virtual biniIO_t& operator<<(unsigned long _data) { return Write(&_data); }
		virtual biniIO_t& operator<<(float _data) { return Write(&_data); }
		virtual biniIO_t& operator<<(double _data) { return Write(&_data); }
		
		biniIO_t& operator<<(const void* _buffer);
		biniIO_t& operator>>(void* _buffer);
		
		void operator,(unsigned int _size) { if(m_isWrite) Write(m_buffer, _size); else Read(m_buffer, _size);}

	//protected:
		/* data */
		//FILE* m_file;
		
		/* static data */
		//static string m_modeTable[];
		
	//protected:
		//void SetStatus(status_e _status) {m_status = _status;}
		//bool IsValidMode(const string& _mode) const;
		
	private:
		void* m_buffer;
		bool m_isWrite;
		
	private:
		template<class T>
		T* Read(T* _data, unsigned int _size = sizeof(T));
		template<class T>
		biniIO_t& Write(const T* _data, unsigned int _size = sizeof(T));
		
		void WriteFromBuffer(unsigned int _size);
		void ReadToBuffer(unsigned int _size);
		
};

template<class T>
T* biniIO_t::Read(T* _data, unsigned int _size)
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
	
	if(fread(_data, _size, 1, m_file) != 1)
	{
		SetStatus(writeErr_e);
		throw writeErr_e;
	}
	
	SetStatus(ok_e);
	return _data;
}

template<class T>
biniIO_t& biniIO_t::Write(const T* _data, unsigned int _size)
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
	
	if(fwrite(_data, _size, 1, m_file) != 1)
	{
		SetStatus(readErr_e);
		throw readErr_e;
	}
	
	SetStatus(ok_e);
	return *this;
}

#endif /* __BINI_IO_H__ */

