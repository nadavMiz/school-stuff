#include <stdio.h>
#include <string>

#include "virtIO.h"

using namespace std;

string virtIO_t::m_modeTable[] = {"r", "w", "a", "r+", "w+", "a+"};

virtIO_t::virtIO_t()
{
	m_access = "";
	m_file = 0;
	m_status = bad_access_e;
	m_path = "";
	
}

virtIO_t::virtIO_t(const string& _path, const string& _mode)
{
	if(IsValidMode(_mode))
	{
		m_access = _mode;
	}
	else
	{
		m_access = "";
	}
	
	m_file = 0;
	m_path = _path;
	m_status = bad_access_e;
}


virtIO_t::~virtIO_t()
{
	if(0 != m_file)
	{
		SetStatus(bad_access_e);
		fclose(m_file);
	}
}

virtIO_t::status_e virtIO_t::OpenFile()
{
	m_file = fopen(m_path.c_str(), m_access.c_str());
	
	if(0 == m_file)
	{
		SetStatus(cant_open_file_e);
		return cant_open_file_e;
	}
	
	SetStatus(ok_e);
	return ok_e;
}

virtIO_t::status_e virtIO_t::Open()
{
	if(0 != m_file)
	{
		SetStatus(cant_open_file_e);
		return cant_open_file_e;
	}
	
	return OpenFile();
}

virtIO_t::status_e virtIO_t::Open(const string& _name, const string& _mode)
{
	if(!IsValidMode(_mode) || 0 != m_file)
	{
		SetStatus(cant_open_file_e);
		return cant_open_file_e;
	}
	
	m_access = _mode;
	m_path = _name;
	
	return OpenFile();
}

void virtIO_t::close()
{
	if(0 == m_file)
	{
		return;
	}
	
	fclose(m_file);
	m_file = 0;
}

bool virtIO_t::IsValidMode(const string& _mode) const
{
	for(int i = 0; i < 6; ++i)
	{
		if(_mode == m_modeTable[i])
		{
			return true;
		}
	}
	
	return false;
}


long int virtIO_t::Length() const
{
	if(0 == m_file)
	{
		return 0;
	}
	
	long int currentPos = ftell(m_file);
	
	fseek(m_file, 0L, SEEK_END);
	long int length = ftell(m_file);
	
	fseek(m_file, currentPos, SEEK_SET);
	
	return length;
}

virtIO_t::status_e virtIO_t::SetPosition(long int _position)
{
	if(0 == m_file)
	{
		return bad_access_e;
	}
	
	if(0 != fseek(m_file, _position, SEEK_SET))
	{
		return bad_access_e;
	}
	
	return ok_e;
}
