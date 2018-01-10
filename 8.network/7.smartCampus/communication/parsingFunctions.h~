#ifndef __PARSING_FUNCTIONS_H__
#define __PARSING_FUNCTIONS_H__

#include <string>
#include <sstream>

#include "eventImp.h"

namespace smartCampus
{
namespace ParsingFunctions
{

void ParseKeyValue(const std::string& _str, std::string& _key, std::string& _value);

template<class T>
std::string GetPair(const std::string& _key, const T& _value);


/*------------------------------------------------------------------------------*/

template <class T>
std::string GetPair(const std::string& _key, const T& _value)
{
	std::stringstream result;
	
	result << _key << EventImp::m_keyValueDelim << _value;
	return result.str();
}

}
}

#endif /*__PARSING_FUNCTIONS_H__*/
