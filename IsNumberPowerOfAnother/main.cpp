/**
https://stackoverflow.com/questions/4429044/check-if-one-integer-is-an-integer-power-of-another
https://www.geeksforgeeks.org/check-if-a-number-is-power-of-another-number/

Check if a number is a power of another number
Given two positive numbers x and y, check if y is a power of x or not. */

#include <iostream>
#include <math.h>
using namespace std;

static bool IsPowerV1(const long x, const long y)
{
    // logarithm function to calculate value
    /**! IN CODEBLOCKS THIS OPERATION TO INT DOES NOT WORK WELL (res1 != res2). IN VSTUDIO YES. (res1 != res2).
    The cast-to-int operation (int)doubleValue performs truncation, which means if the number is represented internally
	as 33.999999999... it will be truncated to 33.
    Use round() if you need to perform rounding (3.9 → 4, 3.4 → 3). */
    //const long res1 = log(y) / log(x);

	const long res1 = round(log(y) / log(x));
	const double res2 = log(y) / log(x); // Note : this is double
    cout << "IsPowerV1: " << res1 << " : " << res2 << endl;

	// compare to the result1 or result2 both are equal
	return x > 0 && y > 0 && res1 == res2;
}

static bool IsPowerV2(const int x, const int y)
{
    // using less log operations
    const double power = log(y) / log(x);
    const double fpower = floor(power);
    cout << "IsPowerV2: " << power << " : " << fpower << endl;
    return x > 0 && y > 0 && power == fpower;
}

static bool IsPowerV3(const int x, int y)
{
    // using a loop
    if (x == 0 || y == 0) { return false; }

    while(y % x == 0){ y /= x; }
    cout << "IsPowerV3: " << x << " : " << y << endl;
    return y == 1;
}

int main()
{
    const long x = 2; //27
    const long y = 8; //729

    bool isPower = IsPowerV1(x, y);
    cout << y << (isPower ? " is power of " : " is not is power of ") << x << endl;

    isPower = IsPowerV2(x, y);
    cout << y << (isPower ? " is power of " : " is not is power of ") << x << endl;

    isPower = IsPowerV3(x, y);
    cout << y << (isPower ? " is power of " : " is not is power of ") << x << endl;
    return 0;
}
