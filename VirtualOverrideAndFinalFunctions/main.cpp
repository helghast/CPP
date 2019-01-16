#include <iostream>
#include <typeinfo>

using namespace std;

class Foo{
public:
    void func1() { func4(__PRETTY_FUNCTION__); };
    virtual void func2() { func4(__PRETTY_FUNCTION__); };
    virtual void func3() final { func4(__PRETTY_FUNCTION__); }; //final keyword prevent child classes to override functions
protected:
    virtual void func4(const char* str) final { cout << str << ":" << typeid(*this).name() << endl; };
};

class Fee : public Foo{
public:
    /*virtual */void func2() override { func4(__PRETTY_FUNCTION__); };
    //virtual void func3() override; //this will make a compilation error
};

int main()
{
    Foo a;
    a.func1();

    Fee b;
    b.func1();
    b.func2();
    b.Foo::func2();
    b.func3(); //child class cant override but can use base class function

    return 0;
}
