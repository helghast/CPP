/**
https://en.wikipedia.org/wiki/SOLID
https://en.wikipedia.org/wiki/Liskov_substitution_principle
https://www.udemy.com/patterns-cplusplus/

Objects in a program should be replaceable with instances of their subtypes w/o altering the correctness of the program
This principle is just an extension of the Open Close Principle and it means that we must make sure that new derived classes are
extending the base classes without changing their behavior.
*/

#include <iostream>
#include <vector>
#include <string>
using namespace std;
#define PI 3.1416f

/** Scoped enumerations: There are no implicit conversions from the values of a scoped enumerator to integral types, although
static_cast may be used to obtain the numeric value of the enumerator.
https://en.cppreference.com/w/cpp/language/enum */
enum class Geometries {Rectangle = 0, Square, Circle};
static const string LiteralsShapes[3] = {"Rectangle", "Square", "Circle"};

// START: v0
class Rectangle
{
protected:
	int width, height;
public:
	Rectangle(const int width, const int height):width(width), height(height){}
	virtual void setWidth(const int width){ this->width = width; }
	virtual void setHeigth(const int height){ this->height = height; }
	int getWidth() const { return width; }
	int getHeigth() const { return height; }
	int area() const { return width * height; }
};

class Square : public Rectangle
{
public:
	Square(const int size):Rectangle(size, size){}
	void setWidth(const int width) override { this->width = this->height = width; }
	void setHeigth(const int height) override { this->width = this->height = height; }
};

// this violates the principle if you use a Square
void process(Rectangle& rectangle)
{
	const int w = rectangle.getWidth();
	rectangle.setHeigth(4);
	cout << "Expected area = " << w * 4 << ", got " << rectangle.area() << endl;
}
// END v0

// START v1
/** instead make a factory object, with two methods to create both geometries */
struct RectangleFactory
{
	static Rectangle create_Rectangle(const int width, const int height){ return Rectangle(width, height); }
	static Rectangle create_Square(const int size){ return Square(size); }
};
// END v1

// START v2
/** another solution. make a base abstract class that only has the area method. size properties are for subclasses instead.
but because you cannot instantiate an abstract class, every new shape subclass instance must be a pointer, and the Factory design
pattern is an example of returning a pointer to an abstract class object.
https://stackoverflow.com/questions/2861270/returning-an-abstract-class-from-a-function */
struct Shape
{
private:
	Geometries shapeType;
public:
	Shape(const Geometries shapeType):shapeType(shapeType){}
	virtual int area() const = 0;
	string getName() const { return LiteralsShapes[static_cast<int>(shapeType)]; }
};

struct Rectangle2 : Shape
{
private:
	int width, heigth;
public:
	// dont use getters/setters, use constructor with params instead
	Rectangle2(const int width, const int heigth):Shape(Geometries::Rectangle), width(width), heigth(heigth){}
	int area() const override { return width * heigth; }
};

struct Square2 : Shape
{
private:
	int size;
public:
	Square2(const int size): Shape(Geometries::Square), size(size){}
	int area() const override { return size * size; }
};

struct Circle : Shape
{
private:
	int radius;
public:
	Circle(const int radius): Shape(Geometries::Circle), radius(radius){}
	int area() const override { return  PI * (radius * radius); }
};

// Factory object
struct ShapeFactory
{
	static Shape* create_Rectangle(const int width, const int heigth){ return new Rectangle2(width, heigth); }
	static Shape* create_Square(const int size){ return new Square2(size); }
	static Shape* create_Circle(const int radius){ return new Circle(radius); }
};

int main()
{
	Rectangle r{3, 4};
	process(r); // we expect 12, and got 12, because setHeigt = 4, then 3*4 = 12

	// now we will blow up with a Square
	Square s{5};
	// square override setHeight, then got 4*4=16, but we expects 5*4 = 20
	process(s);

	/** The Rectangle/Square hierarchy violates the Liskov Substitution Principle (LSP)! Square is behaviorally not a correct
	substitution for Rectangle.
	A Square does not comply with the behavior of a rectangle: Changing the height/width of a square behaves differently from changing
	the height/width of a rectangle. Actually, it doesn't make sense to distinguish between the width and the height of a square. */

	/** a valid solution is use a factory object.
	Another solution is make Rectangle and Square not inherint, and implements an interface with area method */
	Rectangle rectangle1 = RectangleFactory::create_Rectangle(2, 6);
	Rectangle square1 = RectangleFactory::create_Square(4);

	cout << "Using RectangleFactory" << endl;
	cout << "Rectangle area: " << rectangle1.area() << endl;
	cout << "Square area: " << square1.area() << endl;

	/** another solution is make Rectangle and Square derive from a Shape class, which dos not enforce any rules regarding with w/h
	and use Factory pattern to return a ptr to base class. Every subclass calculates area itself, and has geometry custom properties
	Note that a Shape ptr is mandatory, because you cannot instantiate a Shape object, and Factory only return Shape ptr. */
	Shape* rectangle = ShapeFactory::create_Rectangle(4, 8);
	Shape* square = ShapeFactory::create_Square(4);
	Shape* circle = ShapeFactory::create_Circle(3);

	// However you can cast the return value.
	Rectangle2* rectangle2 = (Rectangle2*)ShapeFactory::create_Rectangle(4, 8);
	Square2* square2 = (Square2*)ShapeFactory::create_Square(4);
	Circle* circle2 = (Circle*)ShapeFactory::create_Circle(3);

	cout << "Using ShapeFactory" << endl;
	cout << rectangle->getName() << " area: " << rectangle->area() << endl;
	cout << square->getName() << " area: " << square->area() << endl;
	cout << circle->getName() << " area: " << circle->area() << endl;
	cout << rectangle2->getName() << " area: " << rectangle2->area() << endl;
	cout << square2->getName() << " area: " << square2->area() << endl;
	cout << circle2->getName() << " area: " << circle2->area() << endl;

	// container of shapes
	vector<Shape*> shapes{rectangle, square, circle, rectangle2, square2, circle2};
	for(Shape* item : shapes)
	{
		cout << item->getName() << " area: " << item->area() << endl;
	}
    return 0;
}
