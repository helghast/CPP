/**
https://www.geeksforgeeks.org/insertion-sort/
fast with small arrays.
*/
#include <iostream>

using namespace std;

static void insertionSort(int* arr, const int size)
{
	int key, j;
	for (int i = 0; i < size; ++i)
	{
		key = arr[i];
		j = i - 1;

		// move elements for arr[0...i-1], that are greater than key, to one position ahead of their current position
		while (j >= 0 && arr[j] > key)
		{
			arr[j + 1] = arr[j];
			j--;
		}
		arr[j + 1] = key;
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
    insertionSort(arr, sizeArr);
    cout << "Sorted array: ";
    printArray(arr, sizeArr);
    return 0;
}
