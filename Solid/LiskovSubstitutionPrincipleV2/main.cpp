/**
https://en.wikipedia.org/wiki/SOLID
https://en.wikipedia.org/wiki/Liskov_substitution_principle
https://www.tomdalling.com/blog/software-design/solid-class-design-the-liskov-substitution-principle/
https://stackoverflow.com/questions/56860/what-is-an-example-of-the-liskov-substitution-principle
https://www.udemy.com/patterns-cplusplus/

Objects in a program should be replaceable with instances of their subtypes w/o altering the correctness of the program
This principle is just an extension of the Open Close Principle and it means that we must make sure that new derived classes are
extending the base classes without changing their behavior.

Perhaps the previous Rectange-Square inheritance example is not the most enlightening to understand the Liskov Substitution principle.
https://stackoverflow.com/questions/56860/what-is-an-example-of-the-liskov-substitution-principle
Example: When you think of birds, the first thing that comes to mind is that they can fly. But if you think more carefully, not all
birds can fly although they have wings, like the penguins, ostriches, etc.
*/
#include <iostream>
#include <typeinfo>

using namespace std;

// v0. Breaks Liskov principle
struct Bird
{
	virtual void fly() = 0;
};

// OK, ducks can fly
struct Duck : Bird
{
	void fly() override { cout << "Duck can fly" << endl; }
};

// BAD, penguins cannot fly
struct Penguin : Bird
{
	void fly() override { cout << "Penguin can fly. Really?" << endl; }
};

// BAD, penguins cannot fly
struct Ostrich : Bird
{
	void fly() override { cout << "Ostrich can fly. Really?" << endl; }
};

// v1. Maybe add more methods to base struct? Breaks Liskov principle to
struct Bird1
{
	virtual void fly() = 0;
	virtual void swim() = 0;
};

// OK, ducks and can swim over water
struct Duck1 : Bird1
{
	void fly() override{ cout << "Duck can fly" << endl; }
	void swim() override{ cout << "Duck can swin" << endl; }
};

// BAD, penguins cannot fly, but can swim
struct Penguin1 : Bird1
{
	void fly() override{ cout << "Penguin can fly. Really?" << endl; }
	void swim() override{ cout << "Penguin can swin" << endl; }
};

// BAD, ostrich cannot fly and cannot swim. Then we have an useless inheritance here
struct Ostrich1 : Bird1
{
	void fly() override{ cout << "Ostrich can fly. Really?" << endl; }
	void swim() override{ cout << "Ostrich can swin. Really?" << endl; }
};

// v2. The correct way is to make base struct more simple. Ok, i think all the bird can breathe...
struct Bird2
{
	virtual void breathe() = 0;
};

// OK
struct Duck2 : Bird2
{
	void breathe() override{ cout << "Duck can breathe" << endl; }
	void fly() { cout << "Duck can fly" << endl; }
	void swim() { cout << "Duck can swim" << endl; }
};

// OK
struct Penguin2 : Bird2
{
	void breathe() override{ cout << "Penguin can breathe" << endl; }
	void swim() { cout << "Penguin can swim" << endl; }
};

// OK
struct Ostrich2 : Bird2
{
	void breathe() override{ cout << "Ostrich can breathe" << endl; }
};

//v3. of course you can use Interfaces using Interface Segregation Principle, and every subbird struct implement what they need
struct FlyingBirds : Bird2
{
	virtual void fly() = 0;
};

struct SwimmingBirds : Bird2
{
	virtual void swim() = 0;
};

struct Duck3 : FlyingBirds, SwimmingBirds
{
	void breathe() override{ cout << "Duck can breathe" << endl; }
	void fly() override{ cout << "Duck can fly" << endl; }
	void swim() override{ cout << "Ostrich can swim" << endl; }
};

struct Penguin3 : SwimmingBirds
{
	void breathe() override{ cout << "Penguin can breathe" << endl; }
	void swim() override{ cout << "Penguin can swim" << endl; }
};

struct Ostrich3 : Bird2
{
	void breathe() override{ cout << "Ostrich can breathe" << endl; }
};

// breaks the LSP. Solution breaks Open-Closed principle too.
static string CanFly(Bird* bird)
{
	// if you pass a Penguin or a Ostrich then breaks the LSP
	//bird->fly();

	bool canFly = false;

	// You can of course solve it by doing something like this
	Ostrich* aOstrich = dynamic_cast<Ostrich*>(bird);
	Duck* aDuck = dynamic_cast<Duck*>(bird);
	Penguin* aPenguin = dynamic_cast<Penguin*>(bird);
	if (aOstrich)
	{
		canFly = false;
	}
	else if (aDuck)
	{
		bird->fly();
		canFly = true;
	}
	else if (aPenguin)
	{
		canFly = false;
	}

	//But that would break Open-Closed principle and has to be implemented everywhere (and thefore still generates unstable code).
	return canFly ? "yes" : "no";
}

int main()
{
	Duck duck;
	duck.fly(); // OK

	Penguin penguin;
	penguin.fly(); // BAD

	Ostrich ostrich; // BAD
	ostrich.fly();

	Penguin1 p1; // BAD
	p1.fly();
	p1.swim();

	Ostrich1 o1; // BAD
	o1.fly();
	o1.swim();

	Duck2 d2; // OK
	d2.breathe();
	d2.fly();
	d2.swim();

	Penguin2 p2; // OK
	p2.breathe();
	p2.swim();

	Duck3 d3; // OK
	d3.breathe();
	d3.fly();
	d3.swim();

	Penguin3 p3; // OK
	p3.breathe();
	p3.swim();

	Ostrich3 o3; // OK
	o3.breathe();

	FlyingBirds* fb = &d3; // OK
	fb->fly();
	SwimmingBirds* sb = &d3;
	sb->swim();
	Bird2* b2 = fb;
	b2->breathe();

	Bird2* b3 = &o3;
	b3->breathe();

	cout << "Can duck fly? " << CanFly(&duck) << endl;
	cout << "Can penguin fly? " << CanFly(&penguin) << endl;
	cout << "Can ostrich fly? " << CanFly(&ostrich) << endl;
    return 0;
}
