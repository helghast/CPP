/**
https://en.wikipedia.org/wiki/SOLID
https://en.wikipedia.org/wiki/Open–closed_principle
https://www.udemy.com/patterns-cplusplus/

Software entities (classes, modules, functions, etc.) should be open for extension, but closed for modification, that is, such an entity
can allow its behaviour to be extended without modifying its source code.
*/
#include <string>
#include <vector>
#include <iostream>
using namespace std;

// dummies enums
enum class Color{red, green, blue};
enum class Size{small, medium, large};

// dummy data struct
struct Product
{
	string name;
	Color color;
	Size size;
};

//START: the bad filter implementation that violates OpenClosed Principle
struct ProductFilter
{
	//v0
	vector<Product*> by_color(const vector<Product*>& items, const Color color)
	{
		vector<Product*> result;
		for(Product* i : items)
		{
			if(i->color == color)
			{
				result.push_back(i);
			}
		}
		return result;
	}

	//v1. copy and paste by_color and make by_size. only differs in Color/Size
	vector<Product*> by_size(const vector<Product*>& items, const Size size)
	{
		vector<Product*> result;
		for(Product* i : items)
		{
			if(i->size == size)
			{
				result.push_back(i);
			}
		}
		return result;
	}

	//v2. in the futher you or someother add a filter by color and size
	vector<Product*> by_color_and_size(const vector<Product*>& items, const Color color, const Size size)
	{
		vector<Product*> result;
		for(Product* i : items)
		{
			if(i->color == color && i->size == size)
			{
				result.push_back(i);
			}
		}
		return result;
	}

	/** you can see above now the problem. For every search criteria we have been added a new function with a few changes only.
	It is not scalable */
};
// ENDS

// START: to solve this, we will use inheritance and interfaces
// forward declaration for use compact version
template<typename T>
struct AndSpecification;

template<typename T>
struct Specification
{
	virtual bool is_Satisfied(const T* const item) const = 0;

	// more compact using operator && override and calling the AndSpecification constructor
	//AndSpecification<T> operator&&(const Specification<T>&& other)
	AndSpecification<T> operator&&(const Specification<T>& other) { return AndSpecification<T>(*this, other); }
};

template<typename T>
struct Filter
{
	virtual vector<T*> filter(const vector<T*>& items, const Specification<T>& spec) = 0;
};

// now with the base classes/interface we can accomplish OpenClosed principle. Dont edit bases, but extends from them.
struct BetterFilter : Filter<Product>
{
	vector<Product*> filter(const vector<Product*>& items, const Specification<Product>& spec) override
	{
		vector<Product*> result;
		for (Product* item : items)
		{
			if(spec.is_Satisfied(item))
			{
				result.push_back(item);
			}
		}
		return result;
	}
};

// https://en.wikipedia.org/wiki/Specification_pattern
// now, we have a BetterFilter created, we need to create specidifc Specifications to use by BetterFilter
struct ColorSpecification : Specification<Product>
{
	Color color;
	ColorSpecification(const Color color) : color(color){}
	bool is_Satisfied(const Product* const item) const override{ return item->color == color; }
};

// add size spec
struct SizeSpecification : Specification<Product>
{
	Size size;
	SizeSpecification(const Size size) : size(size){}
	bool is_Satisfied(const Product* const item) const override { return item->size == size; }
};
// ENDS

// START: combination specs
template<typename T>
struct AndSpecification : Specification<T>
{
	const Specification<T>& first;
	const Specification<T>& second;
	AndSpecification(const Specification<T>& first, const Specification<T>& second) : first(first), second(second){}
	bool is_Satisfied(const T* const item) const override {	return first.is_Satisfied(item) && second.is_Satisfied(item); }
};
// ENDS

int main()
{
    Product apple{"Apple", Color::green, Size::small}; // use {} if struct has not constructor with params
    Product tree{"Tree", Color::green, Size::large};
    Product house{"House", Color::blue, Size::large};

    const vector<Product*> items{&apple, &tree, &house};

    //open-closed violation version
    ProductFilter pf;
    vector<Product*> green_things = pf.by_color(items, Color::green);
    for(const Product* const item : green_things)
	{
		cout << item->name << " is green" << endl;
	}

	// openclosed version
	BetterFilter bf;
	ColorSpecification greenSpec(Color::green);
	for(Product* item : bf.filter(items, greenSpec))
	{
		cout << item->name << " is green" << endl;
	}

	// START: combination specs
	SizeSpecification largeSpec(Size::large);
	AndSpecification<Product> greenAndLarge(greenSpec, largeSpec);
	for(Product* item : bf.filter(items, greenAndLarge))
	{
		cout << item->name << " is green and large" << endl;
	}
	// ENDS

	// START: more compact using operator && override. more compact way
	AndSpecification<Product> specCompact = ColorSpecification(Color::green) && SizeSpecification(Size::large);
	for(Product* item : bf.filter(items, specCompact))
	{
		cout << item->name << " is green and large" << endl;
	}

	// warning: the following maybe will not compile if you use operator&&(const Specification<T>&& other). Use& instead.
	AndSpecification<Product> specCompact2 = greenSpec && largeSpec;
	for(Product* item : bf.filter(items, specCompact2))
	{
		cout << item->name << " is green and large" << endl;
	}
	// END
    return 0;
}
