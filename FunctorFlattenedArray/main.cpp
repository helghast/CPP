/**
https://www.dotnetperls.com/flatten-array
http://www.cplusplus.com/doc/tutorial/arrays/
https://en.cppreference.com/w/cpp/language/array
http://www.cplusplus.com/forum/beginner/32587/
https://stackoverflow.com/questions/2151084/map-a-2d-array-onto-a-1d-array

Multidimensional arrays tend to be REALLY annoying when you're using arrays of arrays.
A multidimensional array can be flattened. Its dimensions are reduced to one. This transformation yields a single-dimensional array—one
that is simpler and faster. Generally, people use the formula (x*width+y) to simulate a 2d array in a 1d array.

A 2D array is accessed with a Y and then X position. For rectangular arrays (including all 2D arrays and many jagged arrays) you can
use a single array. You multiply the first coordinate by the width, and then add the second coordinate.

The advantages of using a flat array are improved performance and interoperability with C++ or other languages.
*/

#include <iostream>
#include <vector>
#include <algorithm> //for_each
using namespace std;

#define HEIGHT 4 // 4 rows
#define WIDTH 10 // 10 columns
#define ROW_TO_CHANGE 2
#define COLUMN_TO_CHANGE 3
#define VALUE 21

/** A class/struct functor similar to the following could be used and some functor lambdas to iterate through flattened array */
template<typename T>
struct FlattenedArray{
private:
    //T* data; //initial example use a raw array. its nice for the example, but bad to manage. use a vector instead
    std::vector<T> data;
    int height, width;

public:
    FlattenedArray() : data(), height(0), width(0) {}
    FlattenedArray(const int height, const int width) : data(height * width), height(height), width(width) {}
    FlattenedArray(const int height, const int width, const T& value) : data(height * width, value), height(height), width(width) {}
    //~FlattenedArray(){ delete[] data; } //only use dtor if use T* data

    // override () operator
    T& operator()(const int x, const int y){ return data[x * width + y]; }

    void Fill(const T& value){
        for_each(data.begin(), data.end(), [&value](T& element){ element = value; });
    }

    void Iterate(){
        // use "outer" idx variable to do the indexing and capturing and initialized into the lamda. C++14
        // use local ref to private member, to instead use capture this. C++14
        for_each(data.begin(), data.end(), [idx = 0, &refWidth = width](const T& element) mutable
        {
            idx++;
            cout << element << (idx % refWidth == 0 ? "\n" : "\t");
        });
    }
};

/** print elements of raw 2D array. Use a template function to avoid using ugly syntax to pass by reference 2D arrays */
template <typename TwoDArray>
static void print2DArray(const TwoDArray& arr)
{
    for(int i = 0; i < HEIGHT; ++i)
    {
        for (int j = 0; j < WIDTH; ++j)
        {
            cout << arr[i][j] << "\t";
        }
        cout << endl;
    }
}

/** print elements of a raw flattened array. Pass an array. Array decays to a pointer. Thus you lose size information. */
static void printFlattenedArray(const int* const arr)
{
    for(int i = 0; i < HEIGHT; ++i)
    {
        for (int j = 0; j < WIDTH; ++j)
        {
            // to access a flattened array index use the formula (row * width + column)
            cout << arr[i * WIDTH + j] << "\t";
        }
        cout << endl;
    }
}

int main()
{
    // declare a raw 2d-array and initializer can even have no values, thus creates an array of ints each one with a value o zero
    int raw2DArray[HEIGHT][WIDTH] = {};
    cout << "Raw 2D Array" << endl;
    print2DArray(raw2DArray);

    cout << endl << "Access and change raw 2D Array index (" << ROW_TO_CHANGE << ";" << COLUMN_TO_CHANGE << ")= " << VALUE << endl;
    raw2DArray[ROW_TO_CHANGE][COLUMN_TO_CHANGE] = VALUE;
    print2DArray(raw2DArray);

    // multidimensional arrays are just an abstraction for programmers, since the same results can be achieved with a simple array,
    // by multiplying its indices. Example Nbr.1:
    int rawFlattenedArray[HEIGHT * WIDTH] = {};

    // print elements of a raw flattened array
    cout << endl << "Raw Flattened Array" << endl;
    printFlattenedArray(rawFlattenedArray);

    // to access to a flattened array index use the formula (row * width + column)
    cout << endl << "Access and change raw Flattened Array index (" << ROW_TO_CHANGE << ";" << COLUMN_TO_CHANGE << ")= " << VALUE << endl;
    rawFlattenedArray[ROW_TO_CHANGE * WIDTH + COLUMN_TO_CHANGE] = VALUE;
    printFlattenedArray(rawFlattenedArray);
    cout << endl;

    // use a class/struct functor that creates a flattened array. Example Nbr.2:
    FlattenedArray<int> A2DArrayFlattened(HEIGHT, WIDTH, 0); // you can use ctor instead Fill function to fill array
    //A2DArrayFlattened.Fill(0); // you can use function instead ctor to fill array
    //A2DArrayFlattened(1, 3) = 5; // use the overrided () operator and change an array value
    int& value = A2DArrayFlattened(1, 3); // use the overrided () operator to get a reference to an array element
    value = 5;

    cout << "Functor Example Nbr.1" << endl;
    A2DArrayFlattened.Iterate();
    cout << endl;

    // Example Nbr.3:
    FlattenedArray<int>* ptrTo2DArrayFlattened = new FlattenedArray<int>(HEIGHT, WIDTH, 0);
    //ptrTo2DArrayFlattened->Fill(0); // you can use function instead ctor to fill array
    //(*ptrTo2DArrayFlattened)(1, 1) = 128; // use the overrided () operator and change an array value
    int& value2 = (*ptrTo2DArrayFlattened)(1, 1); // use the overrided () operator to get a reference to an array element
    value2 = 128;

    cout << "Functor Example Nbr.2" << endl;
    ptrTo2DArrayFlattened->Iterate();
    return 0;
}
