/**
https://www.udemy.com/patterns-cplusplus/
https://en.wikipedia.org/wiki/Multiton_pattern
https://stackoverflow.com/questions/9631087/multiton-real-world-example
https://stackoverflow.com/questions/2346091/c-templated-class-implementation-of-the-multiton-pattern
In software engineering, the multiton pattern is a design pattern which generalizes the singleton pattern. Whereas the singleton allows
only one instance of a class to be created, the multiton pattern allows for the controlled creation of multiple instances, which it
manages through the use of a map.

example (Java): You have a singleton for every service. Create using enum and store inside a map.
TelephonyManager telephonyManager = (TelephonyManager) getSystemService(Context.TELEPHONY_SERVICE);
InputMethodManager imm = (InputMethodManager) getSystemService(Context.INPUT_METHOD_SERVICE);
ClipboardManager clipboard = (ClipboardManager) getSystemService(CLIPBOARD_SERVICE);

example (Java): Java's ScriptEngine is a good example, only the parameter shows which implementation is used:
ScriptEngine engine = new ScriptEngineManager().getEngineByName("nashorn");
ScriptEngine engine = new ScriptEngineManager().getEngineByName("rhino");
*/

#include <iostream>
#include <map>
#include <memory>
using namespace std;

enum class Importance { primary, secondary, tertiary };

template <typename T, typename Key = std::string>
class Multiton
{
public:
	// if you wanna a polymorphic T
	template <typename V = T>
	static shared_ptr<T> getPolymorphicSharedPtr(const Key& key)
	{
		typename map<Key, shared_ptr<T>>::const_iterator it = instances.find(key);
		if (it != instances.end())
		{
			return it->second;
		}

		shared_ptr<T> instance = make_shared<V>();
		instances[key] = instance;
		return instance;
	}

	static shared_ptr<T> get(const Key& key)
	{
		//because V = T
		return getPolymorphicSharedPtr<T>(key);
	}

	/* using raw ptrs. instead of using map<Key, T*>, you can get a raw ptr from a shared ptr using:
	shared_ptr<Device> m1 = ...;
	Device* ptr = m1.get(); */
	template <typename V>
	static T* getPtr(const Key& key)
	{
		typename map<Key, T*>::const_iterator it = instancesPtr.find(key);
		if (it != instancesPtr.end())
		{
			return (T*)(it->second);
		}

		T* instance = new V();
		instancesPtr[key] = instance;
		return instance;
	}
	// to delete raw ptrs
	static void destroy()
	{
		instancesPtr.clear();
	}

protected:
	Multiton() = default;
	virtual ~Multiton() = default;
private:
	Multiton(const Multiton&) {}
    Multiton& operator= (const Multiton&) { return *this; }

    // using shared_ptr you dont need to implement a destroy() method if T*
	static map<Key, shared_ptr<T>> instances;
	static map<Key, T*> instancesPtr;
};

template <typename T, typename Key> map<Key, shared_ptr<T>> Multiton<T, Key>::instances;
template <typename T, typename Key> map<Key, T*> Multiton<T, Key>::instancesPtr;

class Device
{
protected:
	Device() { print(++Device::totalInstancesCount, "Devices");	}
	static void print(const int Value, const std::string& str)  { cout << "A total of " << Value << " " << str << " instances created so far\n"; }
private:
	static int totalInstancesCount;
};

class Printer : public Device
{
public:
	Printer() {	print(++Printer::totalPrintersCount, "Printers"); }
private:
	static int totalPrintersCount;
};

class Scanner : public Device
{
public:
	Scanner() {	print(++Scanner::totalScannersCount, "Scanners"); }
private:
	static int totalScannersCount;
};

int Device::totalInstancesCount = 0;
int Printer::totalPrintersCount = 0;
int Scanner::totalScannersCount = 0;

int main()
{
    typedef Multiton<Printer, Importance> mt1;
	shared_ptr<Printer> m1 = mt1::get(Importance::primary);
	shared_ptr<Printer> m2 = mt1::get(Importance::secondary);
	shared_ptr<Printer> m3 = mt1::get(Importance::secondary);
	shared_ptr<Printer> m4 = mt1::get(Importance::tertiary);

	typedef Multiton<Device, Importance> mt2;
	shared_ptr<Device> m5 = mt2::getPolymorphicSharedPtr<Printer>(Importance::tertiary);
	shared_ptr<Device> m6 = mt2::getPolymorphicSharedPtr<Scanner>(Importance::primary);
	shared_ptr<Device> m7 = mt2::getPolymorphicSharedPtr<Scanner>(Importance::secondary);

	Printer* m8 = static_cast<Printer*>(mt2::getPtr<Printer>(Importance::primary));
	Scanner* m9 = static_cast<Scanner*>(mt2::getPtr<Scanner>(Importance::tertiary));
	Device* m10 = mt2::getPtr<Printer>(Importance::primary);
	Device* m11 = mt2::getPtr<Scanner>(Importance::tertiary);
	mt2::destroy();
    return 0;
}
