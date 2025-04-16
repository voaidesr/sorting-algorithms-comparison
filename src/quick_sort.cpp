#include "../include/quick_sort.h"

// This version of quickSort selects the middle element as the pivot and partitions the array into two halves.
void quickSortHalfPivot(std::vector<int>& v, int left, int right) {
    if (left >= right) return;

    int pivot = v[(left + right) / 2];
    int i = left, j = right;

    while (i <= j) {
        while (v[i] < pivot) i++;
        while (v[j] > pivot) j--;

        if (i <= j) {
            std::swap(v[i], v[j]);
            i++;
            j--;
        }
    }

    quickSortHalfPivot(v, left, j);
    quickSortHalfPivot(v, i, right);
}

// This version of quickSort selects the median of the first, middle, and last elements as the pivot.
void quickSortMedianPivot(std::vector<int>& v, int left, int right) {
    if (left >= right) return;

    int first = v[left];
    int middle = v[(left + right) / 2];
    int last = v[right];

    int pivot;
    if ((first < middle && middle < last) || (last < middle && middle < first)) {
        pivot = middle;
    } else if ((middle < first && first < last) || (last < first && first < middle)) {
        pivot = first;
    } else {
        pivot = last;
    }

    int i = left, j = right;

    while (i <= j) {
        while (v[i] < pivot) i++;
        while (v[j] > pivot) j--;

        if (i <= j) {
            std::swap(v[i], v[j]);
            i++;
            j--;
        }
    }

    quickSortMedianPivot(v, left, j);
    quickSortMedianPivot(v, i, right);
}

// This version of quickSort selects a random element as the pivot.
#include <cstdlib>
#include <ctime>
void quickSortRandomPivot(std::vector<int>& v, int left, int right) {
    if (left >= right) return;

    size_t randomIndex = left + std::rand() % (right - left + 1);
    int pivot = v[randomIndex];

    int i = left, j = right;

    while (i <= j) {
        while (v[i] < pivot) i++;
        while (v[j] > pivot) j--;

        if (i <= j) {
            std::swap(v[i], v[j]);
            i++;
            j--;
        }
    }

    quickSortRandomPivot(v, left, j);
    quickSortRandomPivot(v, i, right);
}

// This version of quickSort uses a ternary partitioning scheme.
// It divides the array into three parts: less than, equal to, and greater than the pivot.
// Credits to https://catalin.francu.com/ for teaching me this algorithm.
void ternaryQuickSort(std::vector<int>& v, int left, int right) {
    if (left >= right) return;

    int pivot = v[(left + right) / 2];
    int i = left, j = left, k = right;

    while (j <= k) {
        if (v[j] < pivot) {
            std::swap(v[i], v[j]);
            i++;
            j++;
        } else if (v[j] > pivot) {
            std::swap(v[j], v[k]);
            k--;
        } else {
            j++;
        }
    }

    ternaryQuickSort(v, left, i - 1);
    ternaryQuickSort(v, k + 1, right);
}

// Wrapper functions
void quickSortHalfPivot(std::vector<int> &v) { quickSortHalfPivot(v, 0, v.size() - 1); }
void quickSortMedianPivot(std::vector<int> &v) { quickSortMedianPivot(v, 0, v.size() - 1); }
void quickSortRandomPivot(std::vector<int> &v) { quickSortRandomPivot(v, 0, v.size() - 1); }
void ternaryQuickSort(std::vector<int> &v) { ternaryQuickSort(v, 0, v.size() - 1); }
