/**
https://sourcemaking.com/design_patterns/command/cpp/2
Intent
Encapsulate a request as an object, thereby letting you parametrize clients with different requests, queue or log requests, and
support undoable operations.
Promote “invocation of a method on an object” to full object status
An object-oriented callback

Problem
Need to issue requests to objects without knowing anything about the operation being requested or the receiver of the request.

Discussion
Command decouples the object that invokes the operation from the one that knows how to perform it. To achieve this separation, the
designer creates an abstract base class that maps a receiver (an object) with an action (a pointer to a member function). The base
class contains an execute() method that simply calls the action on the receiver.

All clients of Command objects treat each object as a “black box” by simply invoking the object’s virtual execute() method whenever
the client requires the object’s “service”.

A Command class holds some subset of the following: an object, a method to be applied to the object, and the arguments to be passed
when the method is applied. The Command’s “execute” method then causes the pieces to come together.

Sequences of Command objects can be assembled into composite (or macro) commands.

Check list
-Define a Command interface with a method signature like execute().
-Create one or more derived classes that encapsulate some subset of the following: a “receiver” object, the method to invoke,
the arguments to pass.
-Instantiate a Command object for each deferred execution request.
-Pass the Command object from the creator (aka sender) to the invoker (aka receiver).
-The invoker decides when to execute(). */

#include <iostream>
#include <string>
using namespace std;

class Person; //forward declaration

class Command{
    /**1.create a class that encapsulated an object and a member function
    a pointer to a member function (the attributes name is "method")*/
    class Person* object;
    void(Person::* method)();
public:
    Command(Person* obj = nullptr, void(Person::* meth)() = nullptr) : object(obj), method(meth){}
    void execute(){(object->*method)();}
};

class Person{
    string name;
    //cmd is a blackbox, its a method invocation. promoted to full object status
    Command cmd;
public:
    Person(string n, Command c) : name(n), cmd(c){}
    void talk(){
        //this is the sender, cmd has the receiver
        cout << name << " is talking" << endl;
        cmd.execute(); //ask the blackbox to callback the receiver
    }

    void passOn(){
        cout << name << " is passing on" << endl;
        // 4. When the sender is ready to callback to the receiver,
        // it calls execute()
        cmd.execute();
    }

    void gossip(){
        cout << name << " is gossiping" << endl;
        cmd.execute();
    }

    void listen(){ cout << name << " is listening" << endl; }
};
int main()
{
    // Fred will "execute" Barney which will result in a call to passOn()
    // Barney will "execute" Betty which will result in a call to gossip()
    // Betty will "execute" Wilma which will result in a call to listen()
    Person wilma("Wilma", Command());
    // 2. Instantiate an object for each "callback"
    // 3. Pass each object to its future "sender"
    Person betty("Betty", Command(&wilma, &Person::listen));
    Person barney("Barney", Command(&betty, &Person::gossip));
    Person fred("Fred", Command(&barney, &Person::passOn));
    fred.talk();
    return 0;
}
