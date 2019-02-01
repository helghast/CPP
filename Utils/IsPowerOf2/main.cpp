/**
https://stackoverflow.com/questions/108318/whats-the-simplest-way-to-test-whether-a-number-is-a-power-of-2-in-c
https://stackoverflow.com/questions/600293/how-to-check-if-a-number-is-a-power-of-2

Approach #1:
Divide number by 2 reclusively to check it.
Time complexity : O(log2n).

Approach #2:
Bitwise AND the number with its just previous number should be equal to ZERO.
Example: Number = 8; Binary of 8: 1000; Binary of 7: 0111; and the bitwise AND of both the numbers is 0000 = 0.
Time complexity : O(1).

Approach #3:
Bitwise XOR the number with its just previous number should be sum of both numbers.
Example: Number = 8; Binary of 8: 1000; Binary of 7: 0111; and the bitwise XOR of both the numbers is 1111 = 15.
Time complexity : O(1).
*/

#include <iostream>
using namespace std;

// This method checks that a signed 64-bit integer (long) is power of 2:
static bool IsPowerOf2(const long value)
{
    // First check that it is different from 0,
    // then subtract one unit from the number `value`
    // perform the bitwise AND operation,
    // finally check that it equals 0
    // == 0 -> true
    // != 0 -> false
    return value != 0 && (value & (value - 1)) == 0;
}

int main()
{
    long Value = 8;
    bool isPower = IsPowerOf2(Value);
    cout << Value << (isPower ? " is power of 2" : " is not power of 2") << endl;

    Value = 11;
    isPower = IsPowerOf2(Value);
    cout << Value << (isPower ? " is power of 2" : " is not power of 2") << endl;

    return 0;
}
