/**
https://www.geeksforgeeks.org/bubble-sort/
fast to implementate, bad for a huge arrays
*/
#include <iostream>

using namespace std;

// an utility to swap two elements
static void swap(int* a, int* b)
{
    const int temp = *a;
    *a = *b;
    *b = temp;
}

// an optimized version of Bubble Sort
static void bubbleSort(int* arr, const int size)
{
    bool swapped;
    for (int i = 0; i < size - 1; ++i)
    {
        swapped = false;
        for (int j = 0; j < size - i - 1; ++j)
        {
            if (arr[j] > arr[j + 1])
            {
                swap(&arr[j], &arr[j + 1]);
                swapped = true;
            }
        }

        // if no two elements where swapped by inner loop, then break
        if (swapped == false)
        {
            break;
        }
    }
}

/** print elements of a raw array. Pass an array. Array decays to a pointer. Thus you lose size information. */
static void printArray(const int* arr, const int size)
{
    for (int i = 0; i < size; ++i)
    {
        cout << arr[i] << " ";
    }
    cout << endl;
}

int main()
{
    int arr[] = {64, 34, 25, 12, 22, 11, 90};
    const int sizeArr = sizeof(arr)/sizeof(arr[0]);
    bubbleSort(arr, sizeArr);
    cout << "Sorted array: ";
    printArray(arr, sizeArr);
    return 0;
}
