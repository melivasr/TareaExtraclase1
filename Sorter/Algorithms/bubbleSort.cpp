#include "bubbleSort.h"

void bubbleSort(PagedArray& arr, int start, int end) {
    for (int i = start; i < end; i++) {
        for (int j = start; j < end - i; j++) {
            if (arr[j] > arr[j + 1]) {
                std::swap(arr[j], arr[j + 1]);
            }
        }
    }
}
