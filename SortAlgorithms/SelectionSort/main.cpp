/**
https://www.geeksforgeeks.org/selection-sort/
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

static void selectionSort(int* arr, const int size)
{
    int min_idx;
    // one by one move boundary of unsorted subarray
    for (int i = 0; i < size - 1; ++i)
    {
        // find the minimum element in unsorted array
        min_idx = i;
        for (int j = i + 1; j < size; ++j)
        {
            if (arr[j] < arr[min_idx])
            {
                min_idx = j;
            }
        }

        // swap the found minimum element with the first element
        swap(&arr[min_idx], &arr[i]);
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
    int arr[] = {10, 7, 8, 9, 1, 5};
    const int sizeArr = sizeof(arr) / sizeof(arr[0]);
    selectionSort(arr, sizeArr);
    cout << "Sorted array: ";
    printArray(arr, sizeArr);
    return 0;
}
