/**
https://en.wikipedia.org/wiki/SOLID
https://en.wikipedia.org/wiki/Single_responsibility_principle
https://www.udemy.com/patterns-cplusplus/

The single responsibility principle is a computer programming principle that states that every module, class, or function should have
responsibility over a single part of the functionality provided by the software, and that responsibility should be entirely encapsulated
by the class. All its services should be narrowly aligned with that responsibility.
*/

#include <iostream>
#include <string>
#include <vector>
#include <boost/lexical_cast.hpp>
#include <fstream>

using namespace std;

/** The behavior of this Journal class is almost correct, except that it should not perform persistence tasks.
Persistence would be more convenient to delegate to another PersistenceManager class that only performs persistence tasks. */
struct Journal
{
    string title;
    vector<string> entries;

    explicit Journal(const string& title) : title(title){}

    void add(const string& entry)
    {
        static int count = 1;
        entries.push_back(boost::lexical_cast<string>(count++) + ": " + entry);
    }

    // persistence is a seperate concern
    void save(const string& filename)
    {
        // moved responsability to other class
    }
};

// class that only performs persistence tasks.
struct PersistenceManager
{
    static void save(const Journal& j, const string& filename)
    {
        ofstream ofs(filename);
        for (const string& s : j.entries)
        {
            ofs << s << endl;
        }
    }
};

int main()
{
    Journal journal("Dear diary");
    journal.add("I ate a bug");
    journal.add("I dont cried today");

    // SRP violation
    //journal.save("diary.txt");

    // OK
    PersistenceManager::save(journal, "diary.txt");
    return 0;
}
