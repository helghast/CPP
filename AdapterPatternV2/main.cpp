/** 
https://es.wikipedia.org/wiki/Adaptador_(patrón_de_diseño) (original code on Java)
Intent
Convert the interface of a class into another interface clients expect. Adapter lets classes work together that couldn’t otherwise because of incompatible interfaces.
Wrap an existing class with a new interface.
Impedance match an old component to a new system

Problem
An “off the shelf” component offers compelling functionality that you would like to reuse, but its “view of the world” is not compatible with the philosophy and architecture of the system currently being developed.

Discussion
Reuse has always been painful and elusive. One reason has been the tribulation of designing something new, while reusing something old. There is always something not quite right between the old and the new. It may be physical dimensions or misalignment. It may be timing or synchronization. It may be unfortunate assumptions or competing standards.

Adapter is about creating an intermediary abstraction that translates, or maps, the old component to the new system. Clients call methods on the Adapter object which redirects them into calls to the legacy component. This strategy can be implemented either with inheritance or with aggregation.

Adapter functions as a wrapper or modifier of an existing class. It provides a different or translated view of that class.

Check list:
-Identify the players: the component(s) that want to be accommodated (i.e. the client), and the component that needs to adapt (i.e. the adaptee).
-Identify the interface that the client requires.
-Design a “wrapper” class that can “impedance match” the adaptee to the client.
-The adapter/wrapper class “has a” instance of the adaptee class.
-The adapter/wrapper class “maps” the client interface to the adaptee interface.
-The client uses (is coupled to) the new interface

The adapter pattern is used to transform one interface into another, so that one class that can not use the first makes use of it through the second.
It converts the interface of a class into another interface that the client expects. The adapter allows classes to work together, which would not otherwise be possible due to their incompatible interfaces.
This second version creates an abstract/interface class, from which two types of guitars inherit. The first one implements the abstract methods, but the second one has a composition of an adapter object that it will use within the abstract methods of the first one.*/

#include <iostream>
using namespace std;

//desired interface. pure abstract class
class Guitar{
public:
    virtual void onGuitar() = 0;
    virtual void offGuitar() = 0;
};

//class to Adapter/Wrapper 
class AcousticGuitar{
public:
    AcousticGuitar(){}
    void play(){cout << "playing acoustic guitar" << endl;}
    void leaveGuitar(){cout << "i'm tired to play acoustic the guitar" << endl;}
};

class ElectricGuitar : public Guitar{
public:
    ElectricGuitar(){}
    void onGuitar(){cout << "playing electric guitar" << endl;}
    void offGuitar(){cout << "i'm tired to play electric the guitar" << endl;}
};

//adapter/wrapper AcousticGuitar into ElectricAcousticGuitar to adapt into the GuitarModel
class ElectricAcousticGuitar : public Guitar{
private:
    AcousticGuitar* acoustic = new AcousticGuitar();
public:
    ElectricAcousticGuitar(){}
    void onGuitar(){acoustic->play();}
    void offGuitar(){acoustic->leaveGuitar();}
};

int main()
{
    Guitar* eguitar = new ElectricGuitar();
    eguitar->onGuitar();
    eguitar->offGuitar();
    Guitar* eaguitar = new ElectricAcousticGuitar();
    eaguitar->onGuitar();
    eaguitar->offGuitar();
    return 0;
}
