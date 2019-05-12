# Multiton Pattern

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

https://www.udemy.com/patterns-cplusplus/
https://en.wikipedia.org/wiki/Multiton_pattern
https://stackoverflow.com/questions/9631087/multiton-real-world-example
https://stackoverflow.com/questions/2346091/c-templated-class-implementation-of-the-multiton-pattern