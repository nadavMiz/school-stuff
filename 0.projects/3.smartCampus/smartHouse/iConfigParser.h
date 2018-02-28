#ifndef __ICONFIG_PARSER_H__
#define __ICONFIG_PARSER_H__

#include "uncopyable.h"
#include "agentData.h"
#include "nlogFactory.h"

class IConfigParser: private Uncopyable
{
public:
	//IConfigParser();
	virtual ~IConfigParser() = 0;
	virtual void Parse(const std::string& _consfigPath) = 0;
	virtual bool GetNext(AgentData& _data, std::string& _soName) = 0;
	virtual bool IsEndOfFile() const = 0;
	inline static void SetDefaultLogName(const std::string& _newName);

protected:
	inline const std::string& GetDefaultLogName();
	
private:
	static std::string m_defaultLogName;
};


inline void IConfigParser::SetDefaultLogName(const std::string& _newName) 
{
	m_defaultLogName = _newName;
}

inline const std::string& IConfigParser::GetDefaultLogName()
{
	return m_defaultLogName;
}

#endif /* __ICONFIG_PARSER_H__ */

