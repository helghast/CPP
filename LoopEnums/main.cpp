#include <iostream>
#include <vector>

using namespace std;

/** make aware that all the enum values are not assgined manually and you can use a foor loop or a vector */
enum Foo{
    One,
    Two,
    Three,
    Last
};

int main()
{
    /** using a foo with a enum, dont show the Last member. But in this example the Last element is meant to be skipped. 
	Is a fake enum member */
    for (int i = Foo::One; i < Foo::Last; ++i) {
        const Foo testFoo = static_cast<Foo>(i);
        cout << "1.Foo value: " << testFoo << endl;
    }

    /** if wanna show the last member use "<=" */
    for (int i = Foo::One; i <= Foo::Last; ++i) {
        const Foo testFoo = static_cast<Foo>(i);
        cout << "2.Foo value: " << testFoo << endl;
    }

    /** using a vector of enums insted. you can fill using a foorloop, or if enum has few member add manually */
    vector<Foo> vEnums;
    for (int i = Foo::One; i <= Foo::Last; ++i) {
        Foo testFoo = static_cast<Foo>(i);
        vEnums.push_back(testFoo);
        cout << "3.Foo value: " << i << "; Vector value: " << vEnums[i] << endl;
    }

    /** loop vector to see if yet exist Foo's */
    for (std::vector<Foo>::iterator It = vEnums.begin(); It != vEnums.end(); ++It) {
        cout << "4.Vector value: " << *It << endl;
    }
    return 0;
}
