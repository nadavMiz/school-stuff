#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define PHASE (2)

/***** Phase 1 *****{{ */
#if PHASE >= 1
class Point2D
{
public:
	Point2D();
	Point2D(double _x, double _y);

	double GetX() const;
	double GetY() const;
	double Distance(const Point2D& _other) const;

	Point2D &operator+=(const Point2D& _other);
	Point2D &operator*=(double _factor);

private:
	double m_x;
	double m_y;		
};


Point2D::Point2D()
: m_x(0), m_y(0)
{
}

Point2D::Point2D(double _x, double _y)
: m_x(_x), m_y(_y)
{
}

inline double Point2D::GetX() const
{
	return m_x;
}

inline double Point2D::GetY() const
{
	return m_y;
}

double Point2D::Distance(const Point2D& _other) const
{
	double dx = m_x - _other.m_x;
	double dy = m_y - _other.m_y;
	return sqrt(dx * dx + dy * dy);
}

Point2D& Point2D::operator+=(const Point2D& _other)
{
	m_x += _other.m_x;
	m_y += _other.m_y;
	
	return *this;
}

Point2D& Point2D::operator*=(double _factor)
{
	m_x *= _factor;
	m_y *= _factor;
	
	return *this;
}

void pointless()
{
	Point2D p0;
	Point2D p1(0,10);
	printf("distance p0 --> p1 == %f\n", p0.Distance(p1));

	Point2D dxy(+4, -7);
	p1 += dxy;
	printf("%f, %f\n", p1.GetX(), p1.GetY());
	printf("now distance p0 --> p1 == %f\n", p0.Distance(p1));
}

#endif

/* }} ***** Phase 1 *****/


/*----------------------------------------------------------------*/
/***** Phase 2 *****{{ */
#if PHASE >= 2
class NamedPoint2D : public Point2D
{
public:
	NamedPoint2D(const char *_name = "origin");
	NamedPoint2D(double _x, double _y, const char *_name = "anonymous Point");
	NamedPoint2D(const Point2D& point, const char *_name = "anonymous Point");
	const char *GetName() const;

private:
	const char *m_name;	
};


NamedPoint2D::NamedPoint2D(const char *_name)
: m_name(_name)
{
}

NamedPoint2D::NamedPoint2D(double _x, double _y, const char *_name)
: m_name(_name), Point2D(_x, _y)
{
}

NamedPoint2D::NamedPoint2D(const Point2D& _point, const char *_name)
: m_name(_name), Point2D(_point)
{
}

const char *NamedPoint2D::GetName() const
{
	return m_name;
}


/*----------------------------------------------------------------*/

class Rectangle
{
public:
	Rectangle(const Point2D& _a, const Point2D& _b, const char *_name = "anonymous Rectangle");

	const char *GetName() const;
	double CalcArea() const;

private:
	NamedPoint2D m_a;
	Point2D m_b;
	static const int s_curvature = 1;	
};

Rectangle::Rectangle(const Point2D& _a, const Point2D& _b, const char *_name)
: m_a(_a, _name), m_b(_b)
{
}

const char *Rectangle::GetName() const
{
	return m_a.GetName();
}

double Rectangle::CalcArea() const
{
	Point2D p1(m_a.GetX(), m_b.GetY());
	double sideA = m_a.Distance(p1);
	double sideB = m_a.Distance(Point2D(m_b.GetX(), m_a.GetY()));
	return sideA * sideB * s_curvature;
}

/*----------------------------------------------------------------*/

void dog()
{
	NamedPoint2D home(5,7, "home");
	Point2D point(home);
	NamedPoint2D dog(point);

	dog *= 2;
	printf("Distance from %s to %s is %f\n", home.GetName(), dog.GetName(), home.Distance(dog));
}

void area()
{
	Point2D p0;
	Point2D p1(12,12);
	Rectangle r(p0, p1);
	
	printf("The area of %s is %f\n", r.GetName(), r.CalcArea());
	printf("rectangle size %zu\n", sizeof(r));
}

#endif
/* }} ***** Phase 2 *****/

/*----------------------------------------------------------------*/

int main()
{
#if PHASE >= 1
	pointless();
#endif

#if PHASE >= 2
	dog();
	area();
#endif

	return 0;
}

