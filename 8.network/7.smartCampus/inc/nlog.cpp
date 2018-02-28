#include <iostream>
#include <exception>
#include <stdexcept>
#include <fstream>
#include <sstream>
#include <string>

#include "nlog.h"
#include "guard.h"

Nlog::Nlog(const std::string& _path)
{
	if(pthread_mutex_init(&m_mutex, 0) != 0)
	{
		throw std::exception();
	}
	
	m_file.open(_path.c_str(), std::ifstream::out);
	if(m_file.fail())
	{
		throw std::logic_error("cant open file");
	}
}

Nlog::~Nlog()
{
	pthread_mutex_destroy(&m_mutex);
	m_file.close();
}

void Nlog::GetTime(std::string& _time) const
{
	time_t t = time(0);
	struct tm* now = localtime(&t);
    std::stringstream timeStamp; 
    timeStamp << now->tm_hour << "::" << now->tm_min << "::" << now->tm_sec;
    _time = timeStamp.str();
}

void Nlog::write(const std::string& _data, const std::string _deviceId)
{
	std::string time;
	GetTime(time);
	
	std::string toWrite = time + " " + _deviceId + ": " + _data + "\n";
	
	{
		Guard guard(&m_mutex);
		m_file.write(toWrite.c_str(), toWrite.size());
	}
}

void Nlog::Flush()
{
	m_file.flush();
}
