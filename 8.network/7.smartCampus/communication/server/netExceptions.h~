#ifndef NET_EXCEPTIONS_H
#define NET_EXCEPTIONS_H

#include <stdexcept> /* exceptions */

namespace netcpp
{

class ReadWrite_error: public std::runtime_error
{
	public:
		explicit ReadWrite_error(const std::string& what_arg);
		explicit ReadWrite_error(const char* what_arg);
		virtual ~ReadWrite_error() throw(){}
};

inline ReadWrite_error::ReadWrite_error(const std::string& what_arg): std::runtime_error(what_arg){}

inline ReadWrite_error::ReadWrite_error(const char* what_arg): std::runtime_error(what_arg){}


/*----------------------------------------------------------------------------------------------------------*/

class BrokenPipe_error: public std::runtime_error
{
	public:
		explicit BrokenPipe_error(const std::string& what_arg);
		explicit BrokenPipe_error(const char* what_arg);
		virtual ~BrokenPipe_error() throw(){}
};

inline BrokenPipe_error::BrokenPipe_error(const std::string& what_arg): std::runtime_error(what_arg){}

inline BrokenPipe_error::BrokenPipe_error(const char* what_arg): std::runtime_error(what_arg){}

/*----------------------------------------------------------------------------------------------------------*/

class BadRequest_error: public std::runtime_error
{
	public:
		explicit BadRequest_error(const std::string& what_arg);
		explicit BadRequest_error(const char* what_arg);
		virtual ~BadRequest_error() throw(){}
};

inline BadRequest_error::BadRequest_error(const std::string& what_arg): std::runtime_error(what_arg){}

inline BadRequest_error::BadRequest_error(const char* what_arg): std::runtime_error(what_arg){}

}
#endif /* NET_EXCEPTIONS_H */

