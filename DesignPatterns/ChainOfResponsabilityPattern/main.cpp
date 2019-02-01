/**
https://sourcemaking.com/design_patterns/chain_of_responsibility/cpp/1
Intent
Avoid coupling the sender of a request to its receiver by giving more than one object a chance to handle the request. Chain the
receiving objects and pass the request along the chain until an object handles it.
Launch-and-leave requests with a single processing pipeline that contains many possible handlers.
An object-oriented linked list with recursive traversal.

The pattern chains the receiving objects together, and then passes any request messages from object to object until it reaches an
object capable of handling the message. The number and type of handler objects isn't known a priori, they can be configured
dynamically. The chaining mechanism uses recursive composition to allow an unlimited number of handlers to be linked.

Chain of Responsibility simplifies object interconnections. Instead of senders and receivers maintaining references to all candidate
receivers, each sender keeps a single reference to the head of the chain, and each receiver keeps a single reference to its immediate
successor in the chain.

Make sure there exists a "safety net" to "catch" any requests which go unhandled.

Do not use Chain of Responsibility when each request is only handled by one handler, or, when the client object knows which service
object should handle the request.

Check list
1.Put a "next" pointer in the base class
2.The "chain" method in the base class always delegates to the next object
3.If the derived classes cannot handle, they delegate to the base class
*/

#include <iostream>
#include <vector>
#include <ctime>
using namespace std;

class Base{
    Base* next; //1. next pointer in the base class
public:
    Base():next(nullptr){}
    void setNext(Base* n){next = n;}
    void add(Base* n){ (next) ? next->add(n) : setNext(n); }
    // 2. The "chain" method in the base class always delegates to the next obj
    virtual void handle(const int value) {next->handle(value);}
protected:
    void message(const char* const handler, const char* const state, const int value){
		cout << handler << " " << state << " " << value << " ";
	};
};

class Handler1: public Base{
public:
    /*virtual*/void handle(const int value){
        if(rand() % 3){
            // 3. Don't handle requests 3 times out of 4
            message("H1", "passed", value);
            Base::handle(value); // 3. Delegate to the base class
        }
        else
            message("H1", "handled", value);
    }
};

class Handler2: public Base{
public:
    /*virtual*/void handle(const int value){
        if (rand() % 3){
            message("H2", "passed", value);
            Base::handle(value);
        }
        else
            message("H2", "handled", value);
    }
};

class Handler3: public Base{
public:
    /*virtual*/void handle(const int value){
        if (rand() % 3){
            message("H3", "passed", value);
            Base::handle(value);
        }
        else
            message("H3", "handled", value);
    }
};

int main()
{
    srand(time(0)); // gives the random function a new seed
    Handler1 root;
    Handler2 two;
    Handler3 thr;
    root.add(&two);
    root.add(&thr);
    thr.setNext(&root);
    for(int i = 0; i < 10; ++i){
        root.handle(i);
        cout << '\n';
    }
    return 0;
}
