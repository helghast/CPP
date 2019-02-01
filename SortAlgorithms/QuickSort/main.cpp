/**
https://www.geeksforgeeks.org/quick-sort/
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

/* This function takes last element as pivot, places the pivot element at its correct position in sorted array, and places all smaller
(smaller than pivot) to left of pivot and all greater elements to right of pivot */
static int partition(int* arr, const int low, const int high)
{
    const int pivot = arr[high]; // pivot
    int i = low - 1; // index of smaller element

    for (int j = low; j <= high - 1; ++j)
    {
        // if current element is smaller than or equal to pivot
        if (arr[j] <= pivot)
        {
            i++; // increment index of smaller element
            swap(&arr[i], &arr[j]);
        }
    }

    swap(&arr[i + 1], &arr[high]);
    return i + 1;
}

/* The main function that implements QuickSort: arr[] --> Array to be sorted, low  --> Starting index, high  --> Ending index */
static void quickSort(int* arr, const int low, const int high)
{
    if (low < high)
    {
        // pi is partitioning index, arr[p] is now at right place
        int pi = partition(arr, low, high);
        // separately sort elements before partition and after partition
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
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
    quickSort(arr, 0, sizeArr - 1);
    cout << "Sorted array: ";
    printArray(arr, sizeArr);
    return 0;
}
