/**
https://sourcemaking.com/design_patterns/bridge/cpp/1
Intent
Decouple an abstraction from its implementation so that the two can vary independently.
Publish interface in an inheritance hierarchy, and bury implementation in its own inheritance hierarchy.
Beyond encapsulation, to insulation

Problem
“Hardening of the software arteries” has occurred by using subclassing of an abstract base class to provide alternative implementations. This locks in compile-time binding between interface and implementation. The abstraction and implementation cannot be independently extended or composed.

Check list
-Decide if two orthogonal dimensions exist in the domain. These independent concepts could be: abstraction/platform, or domain/infrastructure, or front-end/back-end, or interface/implementation.
-Design the separation of concerns: what does the client want, and what do the platforms provide.
-Design a platform-oriented interface that is minimal, necessary, and sufficient. Its goal is to decouple the abstraction from the platform.
-Define a derived class of that interface for each platform.
-Create the abstraction base class that “has a” platform object and delegates the platform-oriented functionality to it.
-Define specializations of the abstraction class if desired.

Discussion.
The motivation is to decouple the Time interface from the Time implementation, while still allowing the abstraction and the realization to each be modelled with their own inheritance hierarchy. The implementation classes below are straight-forward. The interface classes are a little more subtle. Routinely, a Bridge pattern interface hierarchy "has a" implementation class. Here the interface base class "has a" a pointer to the implementation base class, and each class in the interface hierarchy is responsible for populating the base class pointer with the correct concrete implementation class. Then all requests from the client are simply delegated by the interface class to the encapsulated implementation class. */

#include <iostream>
#include <iomanip> //if do not have this library use cout.precision()
#include <string.h>
using namespace std;

class TimeImp{
public:
    TimeImp(const int hr, const int min):hr(hr), min(min){}
    virtual void tell(){cout << "time is " << setw(2) << setfill('4') << hr << min << endl;}
protected:
    int hr, min;
};

class CivilianTimeImp : public TimeImp{
public:
    CivilianTimeImp(const int hr, const int min, const int pm) : TimeImp(hr, min){ strcpy(whichM_, pm ? " PM" : " AM"); }
    void tell(){cout << "time is " << hr << ":" << min << whichM_ << endl;}
protected:
    char whichM_[4];
};
class ZuluTimeImp : public TimeImp{
public:
    ZuluTimeImp(const int hr, const int min, const int zone) : TimeImp(hr, min){ strcpy(zone_, zone == 5 ? " Eastern Standard Time" : " Central Standard Time"); }
    void tell(){cout << "time is " << setw(2) << setfill('4') << hr << min << zone_ << endl;}
protected:
    char zone_[30];
};

class Time{
public:
    Time(){}
    Time(const int hr, const int min):imp(new TimeImp(hr, min)){}
    virtual void tell(){imp->tell();}
protected:
    TimeImp* imp;
};

class CivilianTime : public Time{
public:
    CivilianTime(const int hr, const int min, const int pm){imp = new CivilianTimeImp(hr, min, pm);}
};
class ZuluTime : public Time{
public:
    ZuluTime(const int hr, const int min, const int zone){imp = new ZuluTimeImp(hr, min, zone);}
};

int main()
{
    Time* times[3] = {new Time(14, 30), new CivilianTime(2, 30, 1), new ZuluTime(14, 30, 6)};
    for(int i = 0; i < 3; ++i)
    {
        times[i]->tell();
    }

    return 0;
}
