#ifndef __THREADABLE_H__
#define __THREADABLE_H__

#ifdef __linux__
#include <tr1/memory> //shared_ptr

#elif defined WIN32

#include <memory> //shared_ptr

#endif /* OS */

namespace advcpp
{
namespace sync
{

template<class Context, void(*Function)(Context&)>
class Threadable
{
public:
	Threadable(const Context& _context);
	//~Threadable();
	//Threadable(const Threadable&);
	//Threadable& operator=(const Threadable&);
	void Run();

private:
	/* data */
	Context m_context;
};

template<class Context, void(*Function)(Context&)>
Threadable<Context, Function>::Threadable(const Context& _context): m_context(_context){}

template<class Context, void(*Function)(Context&)>
void Threadable<Context, Function>::Run()
{
	Function(m_context);
}

}/*namespace sync*/
}/*namespace advcpp*/

#endif /* __THREADABLE_H__ */

