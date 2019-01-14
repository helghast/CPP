/** 
https://sourcemaking.com/design_patterns/adapter/cpp/2
Intent
Convert the interface of a class into another interface clients expect. Adapter lets classes work together that couldn’t otherwise 
because of incompatible interfaces.
Wrap an existing class with a new interface.
Impedance match an old component to a new system

Problem
An “off the shelf” component offers compelling functionality that you would like to reuse, but its “view of the world” is not 
compatible with the philosophy and architecture of the system currently being developed.

Discussion
Reuse has always been painful and elusive. One reason has been the tribulation of designing something new, while reusing something old.
There is always something not quite right between the old and the new. It may be physical dimensions or misalignment. It may be timing 
or synchronization. It may be unfortunate assumptions or competing standards.

Adapter is about creating an intermediary abstraction that translates, or maps, the old component to the new system. Clients call 
methods on the Adapter object which redirects them into calls to the legacy component. This strategy can be implemented either with inheritance or with aggregation.

Adapter functions as a wrapper or modifier of an existing class. It provides a different or translated view of that class.

Check list:
-Identify the players: the component(s) that want to be accommodated (i.e. the client), and the component that needs to adapt 
(i.e. the adaptee).
-Identify the interface that the client requires.
-Design a “wrapper” class that can “impedance match” the adaptee to the client.
-The adapter/wrapper class “has a” instance of the adaptee class.
-The adapter/wrapper class “maps” the client interface to the adaptee interface.
-The client uses (is coupled to) the new interface

The adapter pattern is used to transform one interface into another, so that one class that can not use the first makes use of it 
through the second.
It converts the interface of a class into another interface that the client expects. The adapter allows classes to work together, 
which would not otherwise be possible due to their incompatible interfaces.

External Polymorphism:
1-Specify the new desired interface
2-Design a "wrapper" class that can "impedance match" the old to the new
3-The client uses (is coupled to) the new interface
4-The adapter/wrapper "maps" to the legacy implementation */

#include <iostream>
using namespace std;

class ExecuteInterface{
public:
    //1.especify the new interface
    virtual ~ExecuteInterface(){};
    virtual void execute() = 0;
};
//2.design a "wrapper" or "adapter" class
template<typename T>
class ExecuteAdapter : public ExecuteInterface{
public:
    ExecuteAdapter(T* o, void(T::* m)()):object(o), method(m){}
    ~ExecuteAdapter(){delete object;}
    //4.the adapter/wrapper "maps" the new to the legacy implementation
    void execute() {(object->*method)(); } //the new
private:
    T* object; //ptr to object attribute
    void(T::* method)(); //the old ptr to member function attribute
};

//the old: three totally incompatible classes. no common base class
class Fea{
public:
    //no hope of polymorphism
    ~Fea(){cout << "Fea::dtor" << endl;};
    void doThis(){cout << "Fea::doThis()" << endl;}
};

class Feye{
public:
    ~Feye(){cout << "Feye::dtor" << endl;};
    void doThat(){cout << "Feye::doThat()" << endl;}
};

class Pheau {
public:
  ~Pheau() {cout << "Pheau::dtor" << endl;}
  void doTheOther() {cout << "Pheau::doTheOther()" << endl;}
};

//the new is returned. initialize interface method implementation
ExecuteInterface** initialize(){
    ExecuteInterface** array = new ExecuteInterface* [3];
    //the old is below
    array[0] = new ExecuteAdapter<Fea>(new Fea(), &Fea::doThis);
    array[1] = new ExecuteAdapter<Feye>(new Feye(), &Feye::doThat);
    array[2] = new ExecuteAdapter<Pheau>(new Pheau(), &Pheau::doTheOther);
    return array;
}

int main()
{
    ExecuteInterface** objects = initialize();
    for(int i = 0; i < 3; ++i){objects[i]->execute();}

    //client uses the new polymorphism
    for(int i = 0; i < 3; ++i){delete objects[i];}
    delete objects;
    return 0;
}
