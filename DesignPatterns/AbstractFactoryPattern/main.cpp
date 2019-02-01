/** 
https://sourcemaking.com/design_patterns/abstract_factory
Intent
-Provide an interface for creating families of related or dependent objects without specifying their concrete classes.
-A hierarchy that encapsulates: many possible “platforms”, and the construction of a suite of “products”.
-The new operator considered harmful.

Problem
If an application is to be portable, it needs to encapsulate platform dependencies. These “platforms” might include: windowing system, 
operating system, database, etc. Too often, this encapsulation is not engineered in advance, and lots of #ifdef case statements with 
options for all currently supported platforms begin to procreate like rabbits throughout the code.

Discussion. 
Provide a level of indirection that abstracts the creation of families of related or dependent objects without directly specifying 
their concrete classes. The “factory” object has the responsibility for providing creation services for the entire platform family. 
Clients never create platform objects directly, they ask the factory to do that for them.
This mechanism makes exchanging product families easy because the specific class of the factory object appears only once in the 
application - where it is instantiated. The application can wholesale replace the entire family of products simply by instantiating a 
different concrete instance of the abstract factory.
Because the service provided by the factory object is so pervasive, it is routinely implemented as a Singleton.

"Think of constructors as factories that churn out objects". Here we are allocating the constructor responsibility to a factory object, 
and then using inheritance and virtual member functions to provide a "virtual constructor" capability. So there are two dimensions of 
decoupling occurring. The client uses the factory object instead of "new" to request instances; and, the client "hard-wires" the 
family, or class, of that factory only once, and throughout the remainder of the application only relies on the abstract base class.
Here the client receives a platform-specific factory object, which encapsulates use of "new" operator. Client delegates all creation 
requests to this factory. */

#include <iostream>
#define LINUX
//#define WINDOWS
using namespace std;

/** Abstract base product. It should define an interface which will be common to all products. Clients will work with products 
through this interface, so it should be sufficient to use all products. */
class Widget{
public:
    virtual void draw() = 0;
};

/** concrete product family 1 */
class LinuxButton : public Widget{
public:
    void draw(){cout << "LinuxButton\n";};
};
class LinuxMenu : public Widget{
public:
    void draw(){cout << "LinuxMenu\n";};
};

/** concrete product family 2 */
class WindowsButton : public Widget{
public:
    void draw(){cout << "WindowsButton\n";};
};
class WindowsMenu : public Widget{
public:
    void draw(){cout << "WindowsMenu\n";};
};

/** Abstract factory defines methods to create all related products. */
class Factory{
public:
    virtual Widget* create_button() = 0;
    virtual Widget* create_menu() = 0;
};

/** Each concrete factory corresponds to one product family. It creates all possible products of one kind */
class LinuxFactory : public Factory{
public:
    Widget* create_button(){return new LinuxButton;}
    Widget* create_menu(){return new LinuxMenu;}
};

/** Concrete factory creates concrete products, but returns them as abstract */
class WindowsFactory : public Factory{
public:
    Widget* create_button(){return new WindowsButton;}
    Widget* create_menu(){return new WindowsMenu;}
};

/** Client receives a factory object from its creator. All clients work with factories through abstractinterface. They don't know 
concrete classes of factories. Because of this, you can interchange concrete factories without breaking clients. Clients don't know 
the concrete classes of created products either, since abstract factory methods returns abstract products. */
class Client{
private:
    Factory* factory;
public:
    Client(Factory* f):factory(f){}
    void draw(){
        Widget* w = factory->create_button();
        w->draw();
        display_window_one();
        display_window_two();
    }

    void display_window_one(){
        Widget* w[] = {factory->create_button(), factory->create_menu()};
        const int size = sizeof(w) / sizeof(w[0]);
        for(int i = 0; i < size; ++i){ w[i]->draw();}
    }

    void display_window_two(){
        Widget* w[] = {factory->create_button(), factory->create_menu()};
        const int size = sizeof(w) / sizeof(w[0]);
        for(int i = 0; i < size; ++i){ w[i]->draw();}
    }
};

/** Now the nasty switch statement is needed only once to pick and create a proper factory. Usually that's happening somewhere in 
program initialization code. */
int main()
{
    Factory* factory;
#ifdef LINUX
    factory = new LinuxFactory;
#else   //windows
    factory = new WindowsFactory;
#endif // LINUX
    Client* c = new Client(factory);
    c->draw();
    return 0;
}
