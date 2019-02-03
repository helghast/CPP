/**
https://en.wikipedia.org/wiki/SOLID
https://en.wikipedia.org/wiki/Interface_segregation_principle
https://www.udemy.com/patterns-cplusplus/

no client should be forced to depend on methods it does not use. ISP splits interfaces that are very large into smaller and more
specific ones so that clients will only have to know about the methods that are of interest to them. ISP is intended to keep a system
decoupled and thus easier to refactor, change, and redeploy.
Just with SRP is the most easy to understand and implements.
Take care of YAGNI: you ain't gonna need it.
*/
#include <iostream>
using namespace std;

struct Document{};

// FIRST: have an abstract class/interface totally correct by the moment
struct IMachine
{
	virtual void print(const Document& doc) = 0;
	virtual void scan(const Document& doc) = 0;
	virtual void fax(const Document& doc) = 0;
};

// if you have a class that does all this functionallity, its ok
struct MultyFunctionPrinter : IMachine
{
	void print(const Document& doc) override{};
	void scan(const Document& doc) override{};
	void fax(const Document& doc) override{};
};

// but what happens if you have a simple printer, simple scan and simple fax and you only have IMachine? they need to implement all methods
struct SimplePrinter : IMachine
{
	void print(const Document& doc) override{}; // OK
	void scan(const Document& doc) override{}; // BAD
	void fax(const Document& doc) override{}; // BAD
};
// END

// SOLUTION: we need to segregate the big interface in smaller interfaces, to avoid doing to much in a single interface class
struct IPrinter
{
	virtual void print(const Document& doc) = 0;
};
struct IScanner
{
	virtual void scan(const Document& doc) = 0;
};
struct IFax
{
	virtual void fax(const Document& doc) = 0;
};

// now make a class that do a simple function / implements one interface
struct Printer : IPrinter
{
	void print(const Document& doc) override{};
};

// if you need a more complex machine, that prints and scan for example, then, you can implements both interfaces
struct PrinterAndScanner : IPrinter, IScanner
{
	void print(const Document& doc) override{};
	void scan(const Document& doc) override{};
};

// or instead, create an interface that inherint both interfaces, and our complex machine implements this interface
struct ICompleMachine : IPrinter, IScanner
{
	// you dont needed to keep in function bodies, because, you want ICompleMachine be abstract too
};

struct ComplexMachine : ICompleMachine
{
	void print(const Document& doc) override{};
	void scan(const Document& doc) override{};
};

/** or if we have already implemented Printer, Scanner or Fax classes that inherint from respective Interfaces, we can use a
Decoretor pattern, where overrided methods of ICompleMachine, calls methods of agregated properties printer and scanner */
struct OtherComplexMachine : ICompleMachine
{
private:
	IPrinter& printer; // implements in terms of agregates
	IScanner& scanner;
public:
	OtherComplexMachine(IPrinter& printer, IScanner& scanner): printer(printer), scanner(scanner){}
	void print(const Document& doc) override{ printer.print(doc); };
	void scan(const Document& doc) override{ scanner.scan(doc); };
};
// END

int main()
{
	cout << "Interface Segregation Principle" << endl;

	Document doc;

	// not breaks ISP
	MultyFunctionPrinter mfp;
	mfp.print(doc);
	mfp.scan(doc);
	mfp.scan(doc);

	// breaks ISP and YAGNI. simple printer does not need scan and fax method
	SimplePrinter sp;
	sp.print(doc);
	sp.scan(doc);
	sp.fax(doc);

	// not breaks ISP
	Printer printer;
	printer.print(doc);

	PrinterAndScanner ps;
	ps.print(doc);
	ps.scan(doc);

	ComplexMachine cm;
	cm.print(doc);
	cm.scan(doc);

	OtherComplexMachine ocm(printer, cm);
	ocm.print(doc);
	ocm.scan(doc);

	// using interfaces
	IScanner* isc = &ps;
	isc->scan(doc);

	ICompleMachine* icm = new OtherComplexMachine(printer, cm);
	icm->print(doc);
	icm->scan(doc);
    return 0;
}
