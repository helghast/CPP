/**
https://en.wikipedia.org/wiki/SOLID
https://en.wikipedia.org/wiki/Dependency_inversion_principle
https://www.udemy.com/patterns-cplusplus/

split into 2 different ideas:
A. High-level modules should not depend on low-level modules.
	Both should depend on abstractions.
B. Abstractions should not depend on details.
    Details should depend on abstractions.

A high level class should not depend on a low level class, but both should depend on an abstract class or interface.
Ex: If you have a class with a vector attribute, and iterate from outside on that vector, but that class makes it private, then
we have a problem.
*/
#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <tuple>
using namespace std;

enum class Relationship { parent, child, sibling }; // relations between Person A and Person B

struct Person
{
	string name;
};

typedef vector<tuple<Person, Relationship, Person>> my_tuple;

/** START: v1 is completely valid to use in main()
low-level construct for actually storing relationships */
struct Relationships // low-level module/construct
{
	// a vector of relationships with tuples that stores PersonA and PersonB and the relationship type
	my_tuple relations;
	// provide some sort of API for actually asing elements to this Relations collections
	void add_parent_and_child(const Person& parent, const Person& child)
	{
		//C++11
		relations.push_back(std::make_tuple(parent, Relationship::parent, child));
		relations.push_back(std::make_tuple(child, Relationship::child, parent));
		//C++17
		//relations.push_back({parent, Relationship::parent, child});
	}
};

struct Research // high-level module
{
	// what breaks/violates the DIP-A is to take direct dependendy of a low-level Relationships module. but we will test it
	Research(Relationships& relationship)
	{
		// we will access here to the Relationships details (the vector relations) breaking DIP-B
		my_tuple& relations = relationship.relations;
		// now the high-level is directly dependent on the implementation details of the low-level module.
		// If change relations to private, we are fucked up!
		// C++17 tuple iteration
		/*for (auto&& [first, rel, second] : relations){
			if (first.name == "John" && rel == Relationship::parent){
				cout << "John has a child called " << second.name << endl;
			}
		}*/
		// C++11 tuple iteration
		/*for(int i = 0; i < relations.size(); ++i){
			if(get<0>(relations[i]) == "John" && get<1>(relations[i]) == Relationship::parent){
				cout << "John has a child called " << get<2>(relations[i]).name << endl;
			}
		}*/
		/*for(tuple<Person, Relationship, Person>& item : relations){
			if(get<0>(item).name == "John" && get<1>(item) == Relationship::parent){
				cout << "John has a child called " << get<2>(item).name << endl;
			}
		}*/
		for(my_tuple::const_iterator It = relations.begin(); It != relations.end(); ++It)
		{
			if(get<0>(*It).name == "John" && get<1>(*It) == Relationship::parent)
			{
				cout << "John has a child called " << get<2>(*It).name << endl;
			}
		}
	}
};
// END v1

/** START v2. how would you go about fixing the particular situation where low-level module makes private something accessed from
high-level module. We need to move high-level module code to low-level module, to respect SRP, and next add an abstraction */
// abstraction
struct RelationshipBrowser
{
	virtual vector<Person> find_all_children_of(const string& name) const = 0;
};

struct Relationships2 : RelationshipBrowser // low-level module/construct
{
private:
	my_tuple relations; // making it private, break all code if use Research class instead Research2 class
public:
	void add_parent_and_child(const Person& parent, const Person& child)
	{
		relations.push_back(std::make_tuple(parent, Relationship::parent, child));
		relations.push_back(std::make_tuple(child, Relationship::child, parent));
	}

	vector<Person> find_all_children_of(const string& name) const
	{
		vector<Person> result;
		for(my_tuple::const_iterator It = relations.begin(); It != relations.end(); ++It)
		{
			if(get<0>(*It).name == name && get<1>(*It) == Relationship::parent)
			{
				result.push_back(get<2>(*It));
			}
		}
		return result;
	}
};

struct Research2 // high-level module
{
	/** instead of depend of this details below, depends of the RelationshipBrowser abstraction, like DIP-B says, and by polymorphism
	call find_all_children_of() of Relationships2 */
	/*Research2(Relationships2& relationship){
		my_tuple& relations = relationship.relations;

		for(my_tuple::const_iterator It = relations.begin(); It != relations.end(); ++It){
			if(get<0>(*It).name == "John" && get<1>(*It) == Relationship::parent){
				cout << "John has a child called " << get<2>(*It).name << endl;
			}
		}
	}*/
	Research2(const RelationshipBrowser& browser)
	{
		for(const Person& child : browser.find_all_children_of("John"))
		{
			cout << "John has a child called " << child.name << endl;
		}
	}
};
// END v2

int main()
{
    Person parent{"John"};
    Person child1{"Chris"}, child2{"Matt"};

    // START v1
    Relationships relationships;
    relationships.add_parent_and_child(parent, child1);
    relationships.add_parent_and_child(parent, child2);

    Research r1(relationships);
    // END v1

    /** START v2. how would you go about fixing the particular situation where low-level module makes private something accessed from
    high-level module. We need to move high-level module code to low-level module, to respect SRP, and next add an abstraction */
	Relationships2 relationships2;
    relationships2.add_parent_and_child(parent, child1);
    relationships2.add_parent_and_child(parent, child2);

    Research2 r2(relationships2);
    // END v2

    return 0;
}
