#ifndef __NLOG_FACTORY_H__
#define __NLOG_FACTORY_H__

#include <string>
#include <map>

class Nlog;

class NlogFactory
{
public:
	static NlogFactory& GetNlogFactory() {return m_logFactory;}

	void setPath(const std::string& _newPath) {m_path = _newPath;}
	virtual Nlog* GetLog(const std::string& _name);
	static Nlog* GetLog1(const std::string& _name);

protected:
	~NlogFactory();

protected:
	/* data */
	std::map<std::string, Nlog*> m_logs;
	std::string m_path;
	static NlogFactory m_logFactory;
	
private:
	NlogFactory();
	NlogFactory(const NlogFactory& _factory);
	NlogFactory& operator=(const NlogFactory& _factory);
};

#endif /* __NLOG_FACTORY_H__ */

