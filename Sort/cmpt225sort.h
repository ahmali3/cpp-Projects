//Created by Ahmed Ali
//A few different sorting algorithms implemented in this program

#include<iostream>
#include <fstream>
#include <stdexcept>
using std::cout;
using std::endl;
using std::string;
using std::ifstream;
using std::runtime_error;
using std::min;

template<typename T>
int insertionsort(T arr[], int n){
    int barOp = 0;
    int i,j;
    T key;
    for (i = 1; i < n; i++)
    {
        key = arr[i];
        j = i - 1;
        while (j >= 0 && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j = j - 1;

            barOp++;
        }
        arr[j + 1] = key;
    }
    return barOp;
}
template <typename T>
void swap(T* a, T* b){
    T t = *a;
    *a = *b;
    *b = t;
}
template <typename T>
int partition (T arr[], int low, int high, int &barOp){
    T pivot = arr[high];
    int i = (low - 1); // Index of smaller element

    for (int j = low; j <= high - 1; j++)
    {
        // If current element is smaller than the pivot
        barOp++;

        if (arr[j] < pivot)
        {
            i++; // increment index of smaller element
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}
template <typename T>
void quickSortHelper(T arr[], int low, int high, int &barOp){
    if (low < high)
    {
        /* pi is partitioning index, arr[p] is now
        at right place */
        int pi = partition(arr, low, high, barOp);
        // Separately sort elements before
        // partition and after partition
        quickSortHelper(arr, low, pi - 1,barOp);
        quickSortHelper(arr, pi + 1, high,barOp);
    }
}
template <typename T>
int quicksort(T arr[], int n){
    static int barOp = 0;
    quickSortHelper<T>(arr, 0, n-1, barOp);
    return barOp-1;
}
template <typename T>
void merge(T arr[], int l, int m, int r, int &barOp){
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    /* create temp arrays */
    T L[n1], R[n2];

    /* Copy data to temp arrays L[] and R[] */
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    /* Merge the temp arrays back into arr[l..r]*/
    i = 0; // Initial index of first subarray
    j = 0; // Initial index of second subarray
    k = l; // Initial index of merged subarray
    while (i < n1 && j < n2) {
        barOp++;
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    /* Copy the remaining elements of L[], if there
       are any */
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    /* Copy the remaining elements of R[], if there
       are any */
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}
template <typename T>
int mergesort(T* arr, int n){
    static int barOp = 0;
    int curr_size;
    int left_start;
    for (curr_size=1; curr_size<=n-1; curr_size = 2*curr_size){
        for (left_start=0; left_start<n-1; left_start += 2*curr_size){
            int mid = min(left_start + curr_size - 1, n-1);
            int right_end = min(left_start + 2*curr_size - 1, n-1);
            merge(arr, left_start, mid, right_end,barOp);
        }
    }
    return barOp-1;
}
template <typename T>
int shellsort(T* arr, int n){
    int barOp = 0;
    for (int gap = n/2; gap > 0; gap /= 2)
    {
        for (int i = gap; i < n; i += 1)
        {
            T temp = arr[i];

            int j;
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap){
                arr[j] = arr[j - gap];
                barOp++;
            }
            //  put temp (the original a[i]) in its correct location
            arr[j] = temp;
        }
    }
    return barOp;
}
