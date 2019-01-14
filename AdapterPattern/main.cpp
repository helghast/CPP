/** 
https://sourcemaking.com/design_patterns/adapter/cpp/1
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
This first version creates a pure abstract base class that acts as an interface. A second class that acts as an interface but not pure. A third class that inherits/implements both interfaces, but wants to execute by the method of the first the method of the second. */

#include <iostream>
using namespace std;

typedef int Coordinate;
typedef int Dimension;

//desired interface. pure abstract class
class Rectangle{
public:
    virtual void draw() = 0;
};

//legacy interface.
class LegacyRectangle{
public:
    LegacyRectangle(const Coordinate x1, const Coordinate y1, const Coordinate x2, const Coordinate y2):x1(x1), y1(y1), x2(x2), y2(y2){
        cout << "LegacyRectangle:  create.  ";
        oldDraw();
    }
protected:
    void oldDraw(){ cout << "LegacyRectangle:  oldDraw.  (" << x1 << "," << y1 << ") => (" << x2 << "," << y2 << ")" << endl; }
private:
    Coordinate x1, y1, x2, y2;
};

//adapter / wrapper
class RectangleAdapter : public Rectangle, private LegacyRectangle{
public:
    RectangleAdapter(const Coordinate x, const Coordinate y, const Dimension w, const Dimension h) : LegacyRectangle(x, y, x + w, y + h){
         cout << "RectangleAdapter: create.  (" << x << "," << y << "), width = " << w << ", height = " << h << endl;
    }
    //the first interface method calls the other interface method
    virtual void draw(){
        cout << "RectangleAdapter: draw." << endl;
        oldDraw();
    }
};

int main()
{
    Rectangle* R = new RectangleAdapter(120, 200, 60, 40);
    R->draw();
    return 0;
}
