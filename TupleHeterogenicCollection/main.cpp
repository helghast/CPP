/**
https://en.cppreference.com/w/cpp/utility/tuple
Class template std::tuple is a fixed-size collection of heterogeneous values. It is a generalization of std::pair.

http://www.cplusplus.com/reference/tuple/
Tuple library
Tuples are objects that pack elements of -possibly- different types together in a single object, just like pair objects do for pairs 
of elements, but generalized for any number of elements.
Conceptually, they are similar to plain old data structures (C-like structs) but instead of having named data members, its elements 
are accessed by their order in the tuple.
The selection of particular elements within a tuple is done at the template-instantiation level, and thus, it must be specified at 
compile-time, with helper functions such as get and tie.
The tuple class is closely related to the pair class (defined in header <utility>): Tuples can be constructed from pairs, and pairs 
can be treated as tuples for certain purposes.

array containers also have certain tuple-like functionalities. */

#include <tuple>
#include <iostream>
#include <string>
#include <stdexcept>

std::tuple<double, char, std::string> get_student(int id)
{
    if (id == 0) return std::make_tuple(3.8, 'A', "Lisa Simpson");
    if (id == 1) return std::make_tuple(2.9, 'C', "Milhouse Van Houten");
    if (id == 2) return std::make_tuple(1.7, 'D', "Ralph Wiggum");
    throw std::invalid_argument("id");
}

int main()
{
    auto student0 = get_student(0);
    std::cout << "ID: 0, "
              << "GPA: " << std::get<0>(student0) << ", "
              << "grade: " << std::get<1>(student0) << ", "
              << "name: " << std::get<2>(student0) << '\n';

    std::tuple<double, char, std::string> myTuple = get_student(0);
    std::cout << "ID: 0, "
              << "GPA: " << std::get<0>(myTuple) << ", "
              << "grade: " << std::get<1>(myTuple) << ", "
              << "name: " << std::get<2>(myTuple) << '\n';

    double gpa1;
    char grade1;
    std::string name1;
    std::tie(gpa1, grade1, name1) = get_student(1);
    std::cout << "ID: 1, "
              << "GPA: " << gpa1 << ", "
              << "grade: " << grade1 << ", "
              << "name: " << name1 << '\n';

    // C++17 structured binding:
    /*auto [ gpa2, grade2, name2 ] = get_student(2);
    std::cout << "ID: 2, "
              << "GPA: " << gpa2 << ", "
              << "grade: " << grade2 << ", "
              << "name: " << name2 << '\n';*/



    return 0;
}
