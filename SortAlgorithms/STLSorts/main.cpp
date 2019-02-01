/** http://www.cplusplus.com/reference/algorithm/sort/ */
#include <iostream> //std::cout
#include <algorithm> //std::sort
#include <vector>   //std::vector

using namespace std;

static void printArray(const vector<int>& container)
{
    for (std::vector<int>::const_iterator it = container.begin(); it != container.end(); ++it)
    {
        cout << *it << " ";
    }
    cout << endl << endl;
}

static bool myFunction(const int i, const int j)
{
    return i < j;
}

struct myFunctor
{
    bool operator() (const int i, const int j)
    {
        return i < j;
    }
} myFunctorObject;

int main()
{
    const int arrInts[] = {32, 71, 12, 45, 26, 80, 53, 33};
    const int sizeArr = sizeof(arrInts) / sizeof(arrInts[0]);
    vector<int> vectorInts(arrInts, arrInts + sizeArr);
    cout << "Initial array" << endl;
    printArray(vectorInts);

    cout << "Using default comparision operator <" << endl;
    //std::sort(vectorInts.begin(), vectorInts.begin() + 4);
    std::sort(vectorInts.begin(), vectorInts.end());
    printArray(vectorInts);

    cout << "Using function as comp" << endl;
    vectorInts = {arrInts, arrInts + sizeArr};
    printArray(vectorInts);
    //std::sort (myvector.begin()+4, myvector.end(), myfunction);
    std::sort(vectorInts.begin(), vectorInts.end(), myFunction);
    printArray(vectorInts);

    cout << "Using object as comp" << endl;
    vectorInts = {arrInts, arrInts + sizeArr};
    printArray(vectorInts);
    std::sort(vectorInts.begin(), vectorInts.end(), myFunctorObject);
    printArray(vectorInts);

    return 0;
}
