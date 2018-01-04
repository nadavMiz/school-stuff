#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define PHASE (2)

#if PHASE >= 1

/*
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
};*/

typedef struct
{
	double m_x;
	double m_y;
	
} Point2D;

/*Point2D::Point2D()
: m_x(0), m_y(0)
{
}*/

void Pint2D_Point2DPtr(Point2D* _this)
{	
	if(NULL == _this)
	{
		return;
	}
	
	_this->m_x = 0;
	_this->m_y = 0;
}

/*Point2D::Point2D(double _x, double _y)
: m_x(_x), m_y(_y)
{
}*/
void Point2D_Point2DPtr_Double_double(Point2D* _this ,double _x, double _y)
{	
	_this->m_x = _x;
	_this->m_y = _y;
}

/* default copy CTOR */
void Point2D_Point2DPtr_ConstPoint2D(Point2D* _this, const Point2D* _other)
{
	_this->m_x = _other->m_x;
	_this->m_y = _other->m_y;
}

/*double Point2D::Distance(const Point2D& _other) const
{
	double dx = m_x - _other.m_x;
	double dy = m_y - _other.m_y;
	return sqrt(dx * dx + dy * dy);
}*/
double Point2D_Distance_ConstPoint2DPtr_ConstPoint2DPtr(const Point2D* _this, const Point2D* _other)
{
	double dx;
	double dy;
	
	dx = _this->m_x - _other->m_x;
	dy = _this->m_y - _other->m_y;
	return sqrt(dx * dx + dy * dy);
}


/*Point2D& Point2D::operator+=(const Point2D& _other)
{
	m_x += _other.m_x;
	m_y += _other.m_y;
	
	return *this;
}*/
Point2D* Point2D_operatorAddEqual_Point2DPtr_ConstPoint2DPtr(Point2D* _this, const Point2D* _other)
{
	_this->m_x += _other->m_x;
	_this->m_y += _other->m_y;
	
	return _this;
}


/*Point2D& Point2D::operator*=(double _factor)
{
	m_x *= _factor;
	m_y *= _factor;
	
	return *this;
}*/
Point2D* Point2D_operatorMultEqual_Point2D_Double(Point2D* _this, double _factor)
{
	if(NULL == _this)
	{
		return NULL;
	}
	_this->m_x *= _factor;
	_this->m_y *= _factor;
	
	return _this;
}

/*void pointless()
{
	Point2D p0;
	Point2D p1(0,10);
	printf("distance p0 --> p1 == %f\n", p0.Distance(p1));

	Point2D dxy(+4, -7);
	p1 += dxy;
	printf("%f, %f\n", p1.GetX(), p1.GetY());
	printf("now distance p0 --> p1 == %f\n", p0.Distance(p1));
}*/

void pointless()
{
	Point2D p0, p1, dxy;
	
	Pint2D_Point2DPtr(&p0);
	Point2D_Point2DPtr_Double_double(&p1, 0, 10);
	
	printf("distance p0 --> p1 == %f\n", Point2D_Distance_ConstPoint2DPtr_ConstPoint2DPtr(&p0, &p1));

	Point2D_Point2DPtr_Double_double(&dxy, +4, -7);
	
	Point2D_operatorAddEqual_Point2DPtr_ConstPoint2DPtr(&p1, &dxy);
	printf("%f, %f\n", p1.m_x, p1.m_y);
	printf("now distance p0 --> p1 == %f\n", Point2D_Distance_ConstPoint2DPtr_ConstPoint2DPtr(&p0, &p1));
}

#endif /* PHASE >= 1*/

/*--------------------------------------phase-2---------------------------------------*/
#if PHASE >= 2

/*class NamedPoint2D : public Point2D
{
public:
	NamedPoint2D(const char *_name = "origin");
	NamedPoint2D(double _x, double _y, const char *_name = "anonymous Point");
	NamedPoint2D(const Point2D& point, const char *_name = "anonymous Point");
	const char *GetName() const;
private:
	const char *m_name;	
};

*/
typedef struct
{
	double m_x;
	double m_y;
	const char *m_name;
} NamedPoint2D;


/*NamedPoint2D::NamedPoint2D(const char *_name)
: m_name(_name)
{
}
*/
void NamedPoint2D_NamedPoint2DPtr_ConstCharPtr(NamedPoint2D* _this, const char *_name)
{
	Pint2D_Point2DPtr((Point2D*)_this);
	_this->m_name = _name;
}

/*NamedPoint2D::NamedPoint2D(double _x, double _y, const char *_name)
: m_name(_name), Point2D(_x, _y)
{
}*/
void NamedPoint2D_NamedPoint2DPtr_Double_Double_ConstCharPtr(NamedPoint2D* _this, double _x, double _y, const char *_name)
{
	Point2D_Point2DPtr_Double_double((Point2D*)_this, _x, _y);
	_this->m_name = _name;
}

/*NamedPoint2D::NamedPoint2D(const Point2D& _point, const char *_name)
: m_name(_name), Point2D(_point)
{
}*/
void NamedPoint2D_NamedPoint2DPtr_ConstPoint2DRef_ConstCharPtr(NamedPoint2D* _this, const Point2D* _point, const char* _name)
{
	Point2D_Point2DPtr_ConstPoint2D((Point2D*)_this, _point);
	_this->m_name = _name;
}

/*const char *NamedPoint2D::GetName() const
{
	return m_name;
}*/
const char* NamedPoint2D_GetName_ConstNamedPoint2DPtr(const NamedPoint2D* _this)
{
	return _this->m_name;
}

/*---------------------Rectangle------------------------*/
/*class Rectangle
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
*/
const int NamedPoint2D__static__s_curvature = 1;

typedef struct
{
	NamedPoint2D m_a;
	Point2D m_b;
} Rectangle;

/*Rectangle::Rectangle(const Point2D& _a, const Point2D& _b, const char *_name)
: m_a(_a, _name), m_b(_b)
{
}*/
void Rectangle_RectanglePtr_ConstPoint2DRef_ConstPoint2DRef_ConstCharPtr(Rectangle* _this ,const Point2D* _a, const Point2D* _b, const char *_name)
{
	NamedPoint2D_NamedPoint2DPtr_ConstPoint2DRef_ConstCharPtr(&(_this->m_a), _a, _name);
	Point2D_Point2DPtr_ConstPoint2D(&(_this->m_b), _b);
}

/*const char *Rectangle::GetName() const
{
	return m_a.GetName();
}*/
const char* Rectangle_GetName_ConstRectanglePtr(const Rectangle* _this)
{
	return NamedPoint2D_GetName_ConstNamedPoint2DPtr(&(_this->m_a));
}

/*double Rectangle::CalcArea() const
{
	Point2D p1(m_a.GetX(), m_b.GetY());
	double sideA = m_a.Distance(p1);
	double sideB = m_a.Distance(Point2D(m_b.GetX(), m_a.GetY()));
	return sideA * sideB * s_curvature;
}*/
double Rectangle_CalcArea_ConstRectanglePtr(const Rectangle* _this)
{
	Point2D p1, tmpPoint2D;
	
	double sideA, sideB;
	
	Point2D_Point2DPtr_Double_double(&p1, (_this->m_a).m_x, (_this->m_b).m_y);
	sideA = Point2D_Distance_ConstPoint2DPtr_ConstPoint2DPtr((Point2D*)(&(_this->m_a)), &p1);
	
	Point2D_Point2DPtr_Double_double(&tmpPoint2D, (_this->m_b).m_x, (_this->m_a).m_y);
	sideB = Point2D_Distance_ConstPoint2DPtr_ConstPoint2DPtr((Point2D*)(&(_this->m_a)), &tmpPoint2D);
	
	return sideA * sideB * NamedPoint2D__static__s_curvature;
}

/*-----------------------------------------------------------------------------*/

/*void dog()
{
	NamedPoint2D home(5,7, "home");
	Point2D point(home);
	NamedPoint2D dog(point);

	dog *= 2;
	printf("Distance from %s to %s is %f\n", home.GetName(), dog.GetName(), home.Distance(dog));
}*/
void dog()
{
	NamedPoint2D home, dog;
	Point2D point;
	
	NamedPoint2D_NamedPoint2DPtr_Double_Double_ConstCharPtr(&home, 5, 7, "home");
	Point2D_Point2DPtr_ConstPoint2D(&point, (Point2D*)(&home));
	NamedPoint2D_NamedPoint2DPtr_ConstPoint2DRef_ConstCharPtr(&dog, (Point2D*)&home, "anonymous Point");

	Point2D_operatorMultEqual_Point2D_Double((Point2D*)(&dog), 2);

	printf("Distance from %s to %s is %f\n", NamedPoint2D_GetName_ConstNamedPoint2DPtr(&home),
		   NamedPoint2D_GetName_ConstNamedPoint2DPtr(&dog), Point2D_Distance_ConstPoint2DPtr_ConstPoint2DPtr((Point2D*)(&home), (Point2D*)(&dog)));
}

/*void area()
{
	Point2D p0;
	Point2D p1(12,12);
	Rectangle r(p0, p1);
	
	printf("The area of %s is %f\n", r.GetName(), r.CalcArea());
	printf("rectangle size %zu", sizeof(r));
}*/

void area()
{
	Point2D p0, p1;
	Rectangle r;
	
	Pint2D_Point2DPtr(&p0);
	Point2D_Point2DPtr_Double_double(&p1, 12, 12);
	Rectangle_RectanglePtr_ConstPoint2DRef_ConstPoint2DRef_ConstCharPtr(&r, &p0, &p1, "anonymous Rectangle");
	
	printf("The area of %s is %f\n", Rectangle_GetName_ConstRectanglePtr(&r), Rectangle_CalcArea_ConstRectanglePtr(&r));
	printf("rectangle size %zu\n", sizeof(r));
}

#endif /*PHASE >= 2*/

int main()
{
	#if PHASE >= 1
	pointless();
	#endif
	
	#if PHASE >= 2
	dog();
	area();
	#endif
	
	return 1;
}
