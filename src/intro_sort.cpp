#include "intro_sort.h"
#include <algorithm>
#include <cmath>
#include <functional>

namespace {

const int INSERTION_SORT_THRESHOLD = 16;

void insertionSort(std::vector<int>& v, int begin, int end) {
    for (int i = begin + 1; i < end; ++i) {
        int key = v[i];
        int j = i - 1;
        while (j >= begin && v[j] > key) {
            v[j + 1] = v[j];
            --j;
        }
        v[j + 1] = key;
    }
}

void heapSort(std::vector<int>& v, int begin, int end) {
    std::make_heap(v.begin() + begin, v.begin() + end);
    std::sort_heap(v.begin() + begin, v.begin() + end);
}

int partition(std::vector<int>& v, int low, int high) {
    int pivot = v[high];
    int i = low - 1;
    for (int j = low; j < high; ++j) {
        if (v[j] <= pivot) {
            ++i;
            std::swap(v[i], v[j]);
        }
    }
    std::swap(v[i + 1], v[high]);
    return i + 1;
}

void introSortUtil(std::vector<int>& v, int begin, int end, int depthLimit) {
    int size = end - begin;
    if (size <= 1) return;

    if (size < INSERTION_SORT_THRESHOLD) {
        insertionSort(v, begin, end);
    } else if (depthLimit == 0) {
        heapSort(v, begin, end);
    } else {
        int pivotIndex = partition(v, begin, end - 1);
        introSortUtil(v, begin, pivotIndex, depthLimit - 1);
        introSortUtil(v, pivotIndex + 1, end, depthLimit - 1);
    }
}

} // anonymous namespace

void introSort(std::vector<int>& v) {
    int depthLimit = 2 * std::log2(v.size());
    introSortUtil(v, 0, v.size(), depthLimit);
}
