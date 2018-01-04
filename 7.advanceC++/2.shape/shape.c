#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


/*-------------------------------color------------------------------*/

/*struct Color {
	enum ColorEnum { RED, GREEN, DEFAULT };
	static void setColor(ColorEnum color){		
		static const char * pallete[] = { "\x1B[31m", "\x1B[32m", "\033[0m" };
		std::puts(pallete[color]);
	}
};*/

typedef struct
{
	enum ColorEnum { RED, GREEN, DEFAULT } ColorEnum;
} Color;

/*static void setColor(ColorEnum color){		
		static const char * pallete[] = { "\x1B[31m", "\x1B[32m", "\033[0m" };
		std::puts(pallete[color]);
	}*/
	
void Color__static__setColor(enum ColorEnum color)
{
	static const char * pallete[] = { "\x1B[31m", "\x1B[32m", "\033[0m" };
	
	puts(pallete[color]);
}

/*---------------------------scaleable---------------------------*/

typedef struct Scaleable Scaleable;

/*virtual ~Scaleable() { }*/
/*inline*/ 

void Destroy_Scaleable_ScaleablePtr(Scaleable* _this) { }

/*virtual void scale(double) = 0;*/
void Scaleable_scale_ScaleablePtr_Double(Scaleable* _this, double _doub)
{
	assert(0);
}

/*scaleable vtable*/
void(*__Scaleable_vtable__[])(void*) = {(void(*)(void*))Destroy_Scaleable_ScaleablePtr 
									,(void(*)(void*))Scaleable_scale_ScaleablePtr_Double};
/*class Scaleable {
public:
	virtual ~Scaleable() { }	
	virtual void scale(double) = 0;
};*/
struct Scaleable
{
	void(**__vtable__)(void*);
};

void Scaleable_ScaleablePtr(Scaleable* _this)
{
	*(void(***)(void*))_this = __Scaleable_vtable__;
}

/*-----------------------------shape---------------------------------*/

typedef struct Shape Shape;

/* shape vtable */
void Destroy_Shape_ShapePtr(Shape* _this);
void Shape_draw_ConstShapePtr(const Shape* _this);
void Shape_draw_ConstShapePtr_enumColorEnum(const Shape* _this, enum ColorEnum c);
void Shape_scale_ShapePtr_Double(Shape* _this, double f);
double Shape_area_ConstShapePtr(const Shape* _this);

void(*__Shape_vtable__[])(void*) = 
	{
		 (void(*)(void*))Destroy_Shape_ShapePtr
		,(void(*)(void*))Shape_scale_ShapePtr_Double
		,(void(*)(void*))Shape_draw_ConstShapePtr
		,(void(*)(void*))Shape_draw_ConstShapePtr_enumColorEnum
		,(void(*)(void*))Shape_area_ConstShapePtr
	};
	
int Shape__static__NumOfShapes;	

struct Shape
{
	void(**__vtable__)(void*);
	int m_id;
};

/*Shape() : m_id(++NumOfShapes) {
		std::printf("Shape::Shape() - %d\n", m_id); 
	}*/
void Shape_ShapePtr(Shape* _this)
{
	Scaleable_ScaleablePtr((Scaleable*)_this);
	
	*(void(***)(void*))_this = __Shape_vtable__;
	
	_this->m_id = ++Shape__static__NumOfShapes;
	
	printf("Shape::Shape() - %d\n", _this->m_id);
}

/*virtual void draw() const {
		std::printf("Shape::draw() - %d\n", m_id);		
	}*/
void Shape_draw_ConstShapePtr(const Shape* _this)
{
	printf("Shape::draw() - %d\n", _this->m_id);
}

/*~Shape() {
		draw();
		--NumOfShapes; 
		std::printf("Shape::~Shape - %d\n", m_id);
	}*/
void Destroy_Shape_ShapePtr(Shape* _this)
{
	Shape_draw_ConstShapePtr(_this); /* Draw(const Shape* _this) */
	--Shape__static__NumOfShapes;
	printf("Shape::~Shape - %d\n", _this->m_id);
	
	/*inline destructor*/
}

/*Shape(const Shape& other) : m_id(++NumOfShapes) {
		std::printf("Shape::Shape(Shape&) - %d from - %d\n", m_id, other.m_id);
	}*/
void Shape_ShapePtr_ConstShapeRef(Shape* _this, const Shape* other)
{
	/* default Copy Ctor for Scaleable */
	
	*(void(***)(void*))_this = __Shape_vtable__;
	
	_this->m_id = ++Shape__static__NumOfShapes;
	
	printf("Shape::Shape(Shape&) - %d from - %d\n", _this->m_id, other->m_id);
}

/* void draw(Color::ColorEnum c) const {
		std::printf("Shape::draw(c) - %d\n", m_id);
		Color::setColor(c);
		draw();
		Color::setColor(Color::DEFAULT);
	}*/
void Shape_draw_ConstShapePtr_enumColorEnum(const Shape* _this, enum ColorEnum c)
{
	printf("Shape::draw(c) - %d\n", _this->m_id);
	
	Color__static__setColor(c);
	
	(*(void(***)(const Shape*))_this)[2](_this); /* Draw(const Shape* _this) */
	
	Color__static__setColor(DEFAULT);
}

/*virtual void scale(double f = 1) { 
		std::printf("Shape::scale(%f)\n", f);
	}*/
void Shape_scale_ShapePtr_Double(Shape* _this, double f)
{
	printf("Shape::scale(%f)\n", f);
}

/*virtual double area() const { return -1; }*/
double Shape_area_ConstShapePtr(const Shape* _this){return-1;}

/*static void printInventory() {
		std::printf("Shape::printInventory - %d\n", NumOfShapes);*/
void Shape__static__printInventory_SharePtr()
{
	printf("Shape::printInventory - %d\n", Shape__static__NumOfShapes);
}

/*-----------------------------Circle-------------------------------*/

typedef struct
{
	void(**__vtable__)(void*);
	int m_id;
	double m_radius;
} Circle;

void Destroy_Circle_CirclePtr(Circle* _this);
void Circle_scale_CirclePtr_Double(Circle* _this, double f);
void Circle_Draw_ConstCirclePtr(const Circle* _this);
/*void Shape_draw_ConstShapePtr_enumColorEnum(const Shape* _this, enum ColorEnum c);*/
double Circle_Area_ConstCirclePtr(const Circle* _this);

void(*__Circle_vtable__[])(void*) = 
	{
		 (void(*)(void*))Destroy_Circle_CirclePtr
		,(void(*)(void*))Circle_scale_CirclePtr_Double
		,(void(*)(void*))Circle_Draw_ConstCirclePtr
		,(void(*)(void*))Shape_draw_ConstShapePtr_enumColorEnum
		,(void(*)(void*))Circle_Area_ConstCirclePtr
	};

/*Circle() : m_radius(1) { 
		std::printf("Circle::Circle() - %d, r:%f\n", m_id, m_radius); 
	}*/
void Circle_CirclePtr(Circle* _this)
{
	Shape_ShapePtr((Shape*)_this);
	*(void(***)(void*))_this = __Circle_vtable__;
	
	_this->m_radius = 1;
	printf("Circle::Circle() - %d, r:%f\n", _this->m_id, _this->m_radius); 
}

/*Circle(double r) : m_radius(r) { 
		std::printf("Circle::Circle(double) - %d, r:%f\n", m_id, m_radius); 
	}*/
void Circle_CirclePtr_Double(Circle* _this, double r)
{
	Shape_ShapePtr((Shape*)_this);
	*(void(***)(void*))_this = __Circle_vtable__;
	
	_this->m_radius = r;
	
	printf("Circle::Circle(double) - %d, r:%f\n", _this->m_id, _this->m_radius); 
}


/*Circle(const Circle& other)
	: Shape(other), m_radius(other.m_radius) { 
		std::printf("Circle::Circle(Circle&) - %d, r:%f\n", m_id, m_radius);
	}*/
void Circle_CirclePtr_ConstCircleRef(Circle* _this, const Circle* other)
{
	Shape_ShapePtr_ConstShapeRef((Shape*)_this, (const Shape*)other);
	
	*(void(***)(void*))_this = __Circle_vtable__;
	
	_this->m_radius = other->m_radius;
	
	printf("Circle::Circle(Circle&) - %d, r:%f\n", _this->m_id, _this->m_radius);
}

/*~Circle() { 
		std::printf("Circle::~Circle() - %d, r:%f\n", m_id, m_radius); 
	}*/

void Destroy_Circle_CirclePtr(Circle* _this)
{
	printf("Circle::~Circle() - %d, r:%f\n", _this->m_id, _this->m_radius);
	
	Destroy_Shape_ShapePtr((Shape*)_this);
}

/*void draw() const { 
		std::printf("Circle::draw()  - %d, r:%f\n", m_id, m_radius);
	}*/
void Circle_Draw_ConstCirclePtr(const Circle* _this)
{
	printf("Circle::draw()  - %d, r:%f\n", _this->m_id, _this->m_radius);
}

/*void scale(double f = 2) {
		std::printf("Circle::scale(%f)\n", f);
		m_radius *= f;
	}*/
void Circle_scale_CirclePtr_Double(Circle* _this, double f)
{
	printf("Circle::scale(%f)\n", f);
	_this->m_radius *= f;
}

/*double area() const {
		return m_radius * m_radius * 3.1415;	
	}*/
double Circle_Area_ConstCirclePtr(const Circle* _this)
{
	return _this->m_radius * _this->m_radius * 3.1415;
}

/*double radius() const { 
		std::printf("Circle::draw()  - %d, r:%f\n", m_id, m_radius);
		return m_radius;
	}*/
double Circle_Radius_ConstCirclePtr(const Circle* _this)
{
	printf("Circle::draw()  - %d, r:%f\n", _this->m_id, _this->m_radius);
	return _this->m_radius;
}

/*----------------------------Rectangle-----------------------------*/

typedef struct
{
	void(**__vtable__)(void*);
	int m_id;
	int m_a, m_b;
} Rectangle;

/* rectangle vtable */
void Destroy_Rectangle_RectanglePtr(Rectangle* _this);
void Rectangle_scale_RectanglePtr_Double(Rectangle* _this, double f);
void Rectangle_draw_ConstRectanglePtr(const Rectangle* _this);
void Rectangle_draw_ConstRectanglePtr_enumColorEnum(const Rectangle* _this, enum ColorEnum c);
double Rectangle_area_ConstRectanlePtr(const Rectangle* _this);

void(*__Rectangle_vtable__[])(void*) = 
	{
		 (void(*)(void*))Destroy_Rectangle_RectanglePtr
		,(void(*)(void*))Rectangle_scale_RectanglePtr_Double
		,(void(*)(void*))Rectangle_draw_ConstRectanglePtr
		,(void(*)(void*))Rectangle_draw_ConstRectanglePtr_enumColorEnum
		,(void(*)(void*))Rectangle_area_ConstRectanlePtr
	};

/*Rectangle() : m_a(1), m_b(1) { 
		std::printf("Rectangle::Rectangle() - %d, [%d, %d]\n", m_id, m_a, m_b);
	}*/
void Rectangle_RectanglePtr(Rectangle* _this)
{
	Shape_ShapePtr((Shape*)_this);
	*(void(***)(void*))_this = __Rectangle_vtable__;
	
	_this->m_a = 1;
	_this->m_b = 1;
	printf("Rectangle::Rectangle() - %d, [%d, %d]\n", _this->m_id, _this->m_a, _this->m_b);
}

/*Rectangle(int a) : m_a(a), m_b(a) { 
		std::printf("Rectangle::Rectangle(int) - %d, [%d, %d]\n", m_id, m_a, m_b);
	}*/
void Rectangle_RectanglePtr_Int(Rectangle* _this, int a)
{
	Shape_ShapePtr((Shape*)_this);
	*(void(***)(void*))_this = __Rectangle_vtable__;
	
	_this->m_a = a;
	_this->m_b = a;
	printf("Rectangle::Rectangle(int) - %d, [%d, %d]\n", _this->m_id, _this->m_a, _this->m_b);
}

/*Rectangle(int a, int b) : m_a(a), m_b(b) { 
		std::printf("Rectangle::Rectangle(int, int) - %d, [%d, %d]\n", m_id, m_a, m_b);
	}*/
void Rectangle_RectanglePtr_Int_Int(Rectangle* _this, int a, int b)
{
	Shape_ShapePtr((Shape*)_this);
	*(void(***)(void*))_this = __Rectangle_vtable__;
	
	_this->m_a = a;
	_this->m_b = b;
	
	printf("Rectangle::Rectangle(int, int) - %d, [%d, %d]\n", _this->m_id, _this->m_a, _this->m_b);
}

/*Rectangle(const Rectangle &other ) 
	: m_a(other.m_a), m_b(other.m_b), Shape(other) { 
		std::printf("Rectangle::Rectangle(Rectangle&) - %d, a:%d/%d\n", m_id, m_a, m_b);
	}*/
void Rectangle_RectanglePtr_ConstRectangleRef(Rectangle* _this, const Rectangle* other)
{
	Shape_ShapePtr_ConstShapeRef((Shape*)_this, (const Shape*)other);
	*(void(***)(void*))_this= __Rectangle_vtable__;
	
	_this->m_a = other->m_a;
	_this->m_b = other->m_b;
	
	printf("Rectangle::Rectangle(Rectangle&) - %d, a:%d/%d\n", _this->m_id, _this->m_a, _this->m_b);
}

/*~Rectangle() { 
		std::printf("Rectangle::~Rectangle() - %d, [%d, %d]\n", m_id, m_a, m_b);
	}*/
void Destroy_Rectangle_RectanglePtr(Rectangle* _this)
{
	printf("Rectangle::~Rectangle() - %d, [%d, %d]\n", _this->m_id, _this->m_a, _this->m_b);
	
	Destroy_Shape_ShapePtr((Shape*)_this);
}

/*void draw() const { 
		std::printf("Rectangle::draw()  - %d, [%d, %d]\n", m_id, m_a, m_b);
	}*/
void Rectangle_draw_ConstRectanglePtr(const Rectangle* _this)
{
	printf("Rectangle::draw()  - %d, [%d, %d]\n", _this->m_id, _this->m_a, _this->m_b);
}

/*void draw(Color::ColorEnum c) const {
		std::printf("Rectangle::draw(%d)  - %d, [%d, %d]\n", c, m_id, m_a, m_b);
	}*/
void Rectangle_draw_ConstRectanglePtr_enumColorEnum(const Rectangle* _this, enum ColorEnum c)
{
	printf("Rectangle::draw(%d)  - %d, [%d, %d]\n", c, _this->m_id, _this->m_a, _this->m_b);
}

/*void scale(double f = 4){
		std::printf("Rectangle::scale(%f)\n", f);
		m_a *= f;
		m_b *= f;
	}*/
void Rectangle_scale_RectanglePtr_Double(Rectangle* _this, double f)
{
	printf("Rectangle::scale(%f)\n", f);
	_this->m_a *= f;
	_this->m_b *= f;
}

/*double area() const {
		return m_a * m_b;
	}*/
double Rectangle_area_ConstRectanlePtr(const Rectangle* _this)
{
	return _this->m_a * _this->m_b;
}

/*-----------------------------report-------------------------------*/

/*void report(const Shape& s) {
	std::puts("-----report-----");
	s.draw(); 
	Shape::printInventory();
	std::puts("-----report-----");
}*/
void report_ShapePtr(const Shape* s) 
{
	puts("-----report-----");
	(*(void(***)(const Shape*))s)[2](s); //draw
	Shape__static__printInventory_SharePtr();
	puts("-----report-----");
}

/*inline void draw(Shape& obj) { 
	std::puts("-----draw(Shape&)-----");
	obj.scale();
	obj.draw();	
	std::puts("-----draw(Shape&)-----");
}*/
void draw_ShapePtr(Shape* obj)
{
	puts("-----draw(Shape&)-----");
	(*(void(***)(const Shape*, double))obj)[1](obj, 1); //scale
	(*(void(***)(const Shape*))obj)[2](obj); //draw
	puts("-----draw(Shape&)-----");
}

/*void draw(Circle c) { 
	std::puts("-----draw(Circle)-----");

	static Circle unit(1);
	
	unit.draw();
	unit.scale(3);
	c.draw(); 
	std::puts("-----draw(Circle)-----");
}*/
static Circle draw_Circle__static__unit;
static int draw_Circle__static__isFirstTime = 1;

void draw_Circle(Circle c)
{	
	puts("-----draw(Circle)-----");

	if(draw_Circle__static__isFirstTime)
	{
		Circle_CirclePtr_Double(&draw_Circle__static__unit, 1);
		draw_Circle__static__isFirstTime = 0;
	}
	
	Circle_Draw_ConstCirclePtr(&draw_Circle__static__unit);
	
	/*Circle_scale_CirclePtr_Double(&draw_Circle__static__unit, 3);*/
	printf("Circle::scale(%f)\n", (double)3);
	draw_Circle__static__unit.m_radius *= 3;
	
	Circle_Draw_ConstCirclePtr(&c); 
	puts("-----draw(Circle)-----");
}

/*void doObjArray(){
	Shape objects[] = {
	    Circle(),
	    Rectangle(4),
	    Circle(9)
	};

    for(int i = 0; i < 3; ++i) 
		objects[i].draw();
}*/
void doObjArray()
{
	int i;
	Circle tmpCircle1, tmpCircle2;
	Rectangle tmpRectangle;
	Shape objects[3];
	
	Circle_CirclePtr(&tmpCircle1);
	Shape_ShapePtr_ConstShapeRef((Shape*)&objects[0], (Shape*)&tmpCircle1);
	Destroy_Circle_CirclePtr(&tmpCircle1);
	
	Rectangle_RectanglePtr_Int(&tmpRectangle, 4);
	Shape_ShapePtr_ConstShapeRef((Shape*)&objects[1], (Shape*)&tmpRectangle);
	Destroy_Rectangle_RectanglePtr(&tmpRectangle);
	
	Circle_CirclePtr_Double(&tmpCircle2, 9);
	Shape_ShapePtr_ConstShapeRef((Shape*)&objects[2], (Shape*)&tmpCircle2);
	Destroy_Circle_CirclePtr(&tmpCircle2);
	
	for(i = 0; i < 3; ++i)
	{ 
		Shape_draw_ConstShapePtr(&(objects[i]));
	}
	
	for(i = 2; i >=0; --i)
	{
		Destroy_Shape_ShapePtr(&objects[i]);
	}
}

/*void disappear() {
	std::puts("-----disappear-----");

	Circle defaultCircle();

	std::puts("-----disappear-----");
}*/
void disappear() 
{	
	puts("-----disappear-----");
	
	Circle defaultCircle();
	
	puts("-----disappear-----");
}

/*	template <class T>
	double diffWhenDoubled(T& shape){
	double a0 = shape.area();
	shape.scale(2);
	double a1 = shape.area();
	return a1 - a0;
}*/
double diffWhenDoubled_CircleRef(Circle* _shape)
{
	double a0, a1;
	
	 a0 = (*(double(***)(const Circle*))_shape)[4](_shape); //area
	 (*(void(***)(Circle*, double))_shape)[1](_shape, 2); //scale
	 
	 a1 = (*(double(***)(const Circle*))_shape)[4](_shape); //area
	 
	 return a1 - a0;
}

double diffWhenDoubled_ShapeRef(Shape* _shape)
{
	double a0, a1;
	
	 a0 = (*(double(***)(const Shape*))_shape)[4](_shape); //area
	 (*(void(***)(Shape*, double))_shape)[1](_shape, 2); //scale
	 
	 a1 = (*(double(***)(const Shape*))_shape)[4](_shape); //area
	 
	 return a1 - a0;
}


/*void doPointerArray(){
	std::puts("-----doPointerArray-----");
	Shape *array[] =  {
	    new Circle(),
	    new Rectangle(3),
	    new Circle(4)
	};

    for(int i = 0; i < 3; ++i){ 
		array[i]->scale();
		array[i]->draw();
	}

	std::printf("area: %f\n", diffWhenDoubled(*array[2]));

    for(int i = 0; i < 3; ++i) { 
		delete array[i]; 
		array[i] = 0; 
	}

	std::puts("-----doPointerArray-----");
}*/
void doPointerArray()
{
	Shape* array[3];
	Circle* tmpCircle1, *tmpCircle2;
	Rectangle* tmpRectangle;
	int i;
	
	
	puts("-----doPointerArray-----");
	
	tmpCircle1 = malloc(sizeof(Circle));
	Circle_CirclePtr(tmpCircle1);
	array[0] = (Shape*)tmpCircle1;
	
	tmpRectangle = malloc(sizeof(Rectangle));
	Rectangle_RectanglePtr_Int(tmpRectangle, 3);
	array[1] = (Shape*)tmpRectangle;
	
	tmpCircle2 = malloc(sizeof(Circle));
	Circle_CirclePtr_Double(tmpCircle2, 4);
	array[2] = (Shape*)tmpCircle2;

    for(i = 0; i < 3; ++i)
    { 
		(*(void(***)(Shape*, double))array[i])[1](array[i], 1); /* scale(Shape*) */
		(*(void(***)(Shape*))array[i])[2](array[i]); /* draw(Shape*) */
	}

	printf("area: %f\n", diffWhenDoubled_ShapeRef(array[2]));

    for(i = 0; i < 3; ++i) 
    {
    	(*(void(***)(Shape*))array[i])[0](array[i]); /* DTOR() */
		free(array[i]); 
		array[i] = 0; 
	}

	puts("-----doPointerArray-----");
}

/*void dispose(Rectangle* p){
  delete[] p;
}*/
void dispose_RectanglePtr(Rectangle* p, int _size)
{
	int i;
	for(i = _size - 1; i >= 0; --i)
	{
		(*(void(***)(Rectangle*))(p + i))[0](p + i);
	}
	
	free(p);
}

/*class Empty {
public:
    Empty(int id = 0) { std::printf("Empty::Empty(%d)\n", id); }
   ~Empty() { std::puts("Empty::~Empty()");}	
};*/
typedef struct
{
	char placeHolder;
} Empty;

/*Empty(int id = 0) { std::printf("Empty::Empty(%d)\n", id); }*/
void Empty_EmptyPtr_Int(Empty* _this, int id)
{
	printf("Empty::Empty(%d)\n", id);
}

/*~Empty() { std::puts("Empty::~Empty()");}	*/
void Destroy_Empty_EmtyPtr(Empty* _this)
{
	puts("Empty::~Empty()");
}

/*class EmptyEmpty  : public Empty{
	int m_i;

public:
	EmptyEmpty(int id) : m_i(id){
		 std::printf("EmptyEmpty::EmptyEmpty(%d)\n", m_i); 
	}
};*/
typedef struct
{
	int m_i;
} EmptyEmpty;

/* default DTOR*/
void Destroy_EmptyEmpty_EmptyEmptyPtr(EmptyEmpty* _this)
{
	Destroy_Empty_EmtyPtr((Empty*)_this);
}

/*EmptyEmpty(int id) : m_i(id){
		 std::printf("EmptyEmpty::EmptyEmpty(%d)\n", m_i); 
	}*/
void EmptyEmpty_EmptyEmptyPtr_Int(EmptyEmpty* _this, int id)
{
	Empty_EmptyPtr_Int((Empty*)_this, 0);
	
	_this->m_i = id;
	printf("EmptyEmpty::EmptyEmpty(%d)\n", _this->m_i);
}

/*class EmptyBag {
	Empty e1;
	Empty e2;
	EmptyEmpty ee;
public: 
	EmptyBag() : e2(2), e1(1), ee(2) {
		std::puts("EmptyBag::EmptyBag()");
	}
	~EmptyBag(){
		std::puts("EmptyBag::~EmptyBag");
	}	
};*/
typedef struct
{
	Empty e1;
	Empty e2;
	EmptyEmpty ee;
} EmptyBag;

/*EmptyBag() : e2(2), e1(1), ee(2) {
		std::puts("EmptyBag::EmptyBag()");
	}*/
void EmptyBag_EmptyBagPtr(EmptyBag* _this)
{
	Empty_EmptyPtr_Int(&(_this->e1), 1);
	Empty_EmptyPtr_Int(&(_this->e2), 2);
	EmptyEmpty_EmptyEmptyPtr_Int(&(_this->ee), 2);
	
	puts("EmptyBag::EmptyBag()");
}

/*~EmptyBag(){
		std::puts("EmptyBag::~EmptyBag");
	}	*/
void Destroy_EmptyBag_EmptyBagPtr(EmptyBag* _this)
{
	puts("EmptyBag::~EmptyBag");
	
	Destroy_EmptyEmpty_EmptyEmptyPtr(&(_this->ee));
	Destroy_Empty_EmtyPtr(&(_this->e2));
	Destroy_Empty_EmtyPtr(&(_this->e1));
}

/*------------------------------main--------------------------------*/

int main()
{
	int i;
	Circle c, c2;
	Rectangle s;
	
	/*std::printf("---------------Start----------------\n");
    Circle c;
	Rectangle s(4);*/
	printf("---------------Start----------------\n");
    Circle_CirclePtr(&c);
	Rectangle_RectanglePtr_Int(&s, 4);

	/*std::printf("0.-------------------------------\n");		
	draw(c);*/
	printf("0.-------------------------------\n");
	{
		Circle tmpCircle;
		Circle_CirclePtr_ConstCircleRef(&tmpCircle, &c);
		draw_Circle(tmpCircle);
		Destroy_Circle_CirclePtr(&tmpCircle);
	}

	/*std::printf("+..............\n");		
	draw(c);*/
	printf("+..............\n");		
	{
		Circle tmpCircle;
		Circle_CirclePtr_ConstCircleRef(&tmpCircle, &c);
		draw_Circle(tmpCircle);
		Destroy_Circle_CirclePtr(&tmpCircle);
	}

	/*std::printf("+..............\n");		
    draw(s);*/
	printf("+..............\n");		
    draw_ShapePtr((Shape*)&s);

	/*std::printf("+..............\n");		
	report(c);*/
	printf("+..............\n");		
	report_ShapePtr((Shape*)&c);
	
	/*std::printf("1.-------------------------------\n");	
	
    doPointerArray();*/
	printf("1.-------------------------------\n");	
	
    doPointerArray();

	/*std::printf("2.-------------------------------\n");

    doObjArray();*/
	printf("2.-------------------------------\n");

    doObjArray();

	/*std::printf("3.-------------------------------\n");

    Shape::printInventory();
    Circle c2 = c;
    c2.printInventory();*/
	printf("3.-------------------------------\n");

    Shape__static__printInventory_SharePtr();
    Circle_CirclePtr_ConstCircleRef(&c2, &c);
    Shape__static__printInventory_SharePtr();
	
	/*std::printf("4.-------------------------------\n");
   
    Circle olympics[5];
	std::printf("olympic diff %f\n", diffWhenDoubled(olympics[1]));*/
	printf("4.-------------------------------\n");
   
    Circle olympics[5];
    for(i = 0; i < 5; ++i)
    {
    	Circle_CirclePtr(&olympics[i]);
    }
    
    printf("olympic diff %f\n", diffWhenDoubled_CircleRef(&olympics[1]));

	/*std::printf("5.-------------------------------\n");

    Rectangle *fourRectangles = new Rectangle[4];
    dispose(fourRectangles);*/
	printf("5.-------------------------------\n");

    Rectangle* fourRectangles = malloc(sizeof(int) + sizeof(Rectangle) * 4);
    for(i =  0; i < 4; ++i)
    {
    	Rectangle_RectanglePtr(&(fourRectangles[i]));
    }
    
    dispose_RectanglePtr(fourRectangles, 4);

	/*std::printf("6.-------------------------------\n");
	EmptyBag eb;
	std::printf("Empty things are: %zu %zu %zu", sizeof(Empty), sizeof(EmptyEmpty), sizeof(EmptyBag) );*/
	printf("6.-------------------------------\n");
	
	EmptyBag eb;
	EmptyBag_EmptyBagPtr(&eb);
	
	printf("Empty things are: %zu %zu %zu", sizeof(Empty), sizeof(EmptyEmpty), sizeof(EmptyBag) );

	/*std::printf("7.-------------------------------\n");
	disappear();	*/
	printf("7.-------------------------------\n");
	disappear();	

	/*std::printf("---------------END----------------\n");*/
	printf("---------------END----------------\n");

	/* destroy stack elements*/
	Destroy_EmptyBag_EmptyBagPtr(&eb);
	
	for(i = 4; i >= 0; --i)
    {
    	Destroy_Circle_CirclePtr(&olympics[i]);
    }
    
    Destroy_Circle_CirclePtr(&c2);
    Destroy_Rectangle_RectanglePtr(&s);
    Destroy_Circle_CirclePtr(&c);

	/*destroy global variables*/
	if(!draw_Circle__static__isFirstTime)
	{
		Destroy_Circle_CirclePtr(&draw_Circle__static__unit);
	}

	return 1;
}
