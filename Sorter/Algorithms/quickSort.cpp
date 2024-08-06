#include "quickSort.h"
#include <algorithm>  // Para std::swap

int partition(PagedArray &arr, int start, int end)
{
    int pivot = arr[start];
    int low = start + 1;
    int high = end;

    while (true) {
        while (low <= high && arr[low] <= pivot) {
            low++;
        }
        while (low <= high && arr[high] > pivot) {
            high--;
        }
        if (low > high) {
            break;
        }
        std::swap(arr[low], arr[high]);
    }
    std::swap(arr[start], arr[high]);
    return high;
}

void quickSort(PagedArray &arr, int start, int end)
{
    if (start >= end) {
        return;
    }
    int p = partition(arr, start, end);
    quickSort(arr, start, p - 1);
    quickSort(arr, p + 1, end);
}
