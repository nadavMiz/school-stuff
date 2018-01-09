#include <stdexcept>

#include "parsingFunctions.h"
#include "eventImp.h"

namespace smartCampus
{
namespace ParsingFunctions
{

void ParseKeyValue(const std::string& _str, std::string& _key, std::string& _value)
{
	std::size_t pos = _str.find_first_of(EventImp::m_keyValueDelim);
	if(pos == std::string::npos)
	{
		throw std::runtime_error("invalid syntax");
	}
	
	_key = _str.substr(0, pos);
	_value = _str.substr(pos + 1, _str.size() - pos - 1);
}

}
}


