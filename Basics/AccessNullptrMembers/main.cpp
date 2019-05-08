/**
https://stackoverflow.com/questions/11320822/why-does-calling-method-through-null-pointer-work-in-c
https://stackoverflow.com/questions/9489609/is-calling-a-function-on-a-null-pointer-undefined
https://stackoverflow.com/questions/2533476/what-will-happen-when-i-call-a-member-function-on-a-null-object-pointer
*/

#include <iostream>
using namespace std;

class Foo
{
private:
    int a;

public:
	//calling an empty method through null pointer works
	void method(){}

	//calling a method through a null pointer and accessing a class variable will crash the program.
	//void method(){ a = 4; }

	//calling a non-empty method through null pointer works, while not accessing a class variable.
    /*void method()
    {
        std::cout << "Hi" << std::endl;

        if (this == nullptr)
        {
            return;
        }

        a = 4;
    }*/
};

int main()
{
    //Foo is a nullptr. why does calling method through null pointer works?
    Foo* f = nullptr;
    f->method();
    return 0;
}
