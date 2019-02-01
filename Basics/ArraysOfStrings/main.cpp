/** working with array's of chars and strings */

#include <iostream>
#include <bits/stdc++.h> //for string type

using namespace std;

int main()
{
    /**  an array of chars is the "same" than a ptr to char. ej:
        const char arrayOfChars[] = "blue";
        const char* ptrToChar = arrayOfChars;
    */
    // using a pointer to char
    const char* ptrToChar = "blue";
    // using a string type instead
    const string strType = "red";

    // print a char by index
    cout << "ptrToChar. Print index 1: " << ptrToChar[1] << endl;
    // print the full array of chars using the ptr variable
    cout << "ptrToChar: " << ptrToChar << endl;
    // print a string type
    cout << "strType: " << strType << endl;

    // using a 2D array. first [] for how much strings, and second [] for max string size
    const char color[4][10] = { "blue", "red", "orange", "yellow" };
    // calculate the static array size
    int CSize = sizeof(color) / sizeof(color[0]); //or sizeof(*color);

    // print static array size and content using a raw for
    cout << "\nChar array size = " << CSize << endl;
    for (int i = 0; i < CSize; ++i)
    {
        cout << color[i] << " ";
    }

    // using a pointer to a 1D char array
    const char* ptrColors[] = { "blue", "red", "orange", "yellow" };
    CSize = sizeof(ptrColors) / sizeof(*ptrColors);

    // print static array size and content using a raw for
    cout << "\nChar ptrArray size = " << CSize << endl;
    for (int i = 0; i < CSize; ++i)
    {
        cout << ptrColors[i] << " ";
    }

    //use array of strings
    const string strColors[4] = { "blue", "red", "orange", "yellow" };
    CSize = sizeof(strColors) / sizeof(*strColors);

    // print static array size and content using a raw for
    cout << "\nString Array size = " << CSize << endl;
    for (int i = 0; i < CSize; ++i)
    {
        cout << strColors[i] << " ";
    }

    //use a vector of string
    vector<string> vColors;

    /** add one by one:
        vColors.push_back("blue");
        vColors.push_back("red");
        vColors.push_back("orange");
        vColors.push_back("yellow");
    */

    // or insert and array of strings to a vector of string
    vColors.insert(vColors.end(), strColors, strColors + 4);
    CSize = vColors.size();

    // print a vector of string
    cout << "\nVector size = " << CSize << endl;
    for (int i = 0; i < CSize; ++i)
    {
        cout << vColors[i] << " ";
    }

    return 0;
}
