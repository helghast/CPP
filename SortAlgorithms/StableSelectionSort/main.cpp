/**
https://www.geeksforgeeks.org/stable-selection-sort/
*/
#include <iostream>

using namespace std;

static void selectionSort(int* arr, const int size)
{
    // iterate through array elements
    for (int i = 0; i < size - 1; ++i)
    {
        // loop invariant: elements till a[i - 1] already sorted
        // find minimum element from arr[i] to arr[n - 1]
        int min = i;
        for (int j = i + 1; j < size; ++j)
        {
        	if (arr[min] > arr[j])
			{
				min = j;
			}
        }

        // move minimum element at current i
        int key = arr[min];
        while (min > i)
        {
        	arr[min] = arr[min - 1];
        	min--;
        }
        arr[i] = key;
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
