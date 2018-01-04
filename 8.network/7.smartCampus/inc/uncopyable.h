#ifndef UNCOPYABLE_H
#define UNCOPYABLE_H

class Uncopyable
{
public:
	Uncopyable(){}
	
private:
	/* data */
	Uncopyable(const Uncopyable&);
	Uncopyable& operator=(const Uncopyable&);
};

#endif /* UNCOPYABLE_H */

