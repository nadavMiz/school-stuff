#ifndef __NLOG_H__
#define __NLOG_H__

#include <fstream>
#include <pthread.h>
#include <string>

class Nlog
{
	public:
		Nlog(const std::string& _path);
		virtual ~Nlog();
		
		void write(const std::string& _data, const std::string _deviceId);
		void Flush();

	protected:
		void GetTime(std::string& _time) const;

	private:
		/* data */
		std::ofstream m_file;
		pthread_mutex_t m_mutex;
		
	private:
		Nlog(const Nlog& _log);
		Nlog& operator=(const Nlog& _log);
};

#endif /* __NLOG_H__ */

