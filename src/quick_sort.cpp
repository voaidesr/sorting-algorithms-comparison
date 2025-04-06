#include "quick_sort.h"

// This version of quickSort selects the middle element as the pivot and partitions the array into two halves.
void quickSortHalfPivot(std::vector<int>& v) {
    if (v.size() <= 1) return;

    int pivot = v[v.size() / 2];
    std::vector<int> left, right;

    for (size_t i = 0; i < v.size(); ++i) {
        if (i == v.size() / 2) continue;
        if (v[i] < pivot) left.push_back(v[i]);
        else right.push_back(v[i]);
    }

    quickSortHalfPivot(left);
    quickSortHalfPivot(right);

    v.clear();
    v.insert(v.end(), left.begin(), left.end());
    v.push_back(pivot);
    v.insert(v.end(), right.begin(), right.end());
}

// This version of quickSort selects the median of the first, middle, and last elements as the pivot.
void quickSortMedianPivot(std::vector<int>& v) {
    if (v.size() <= 1) return;

    int first = v[0];
    int middle = v[v.size() / 2];
    int last = v[v.size() - 1];

    int pivot;
    if ((first < middle && middle < last) || (last < middle && middle < first)) {
        pivot = middle;
    } else if ((middle < first && first < last) || (last < first && first < middle)) {
        pivot = first;
    } else {
        pivot = last;
    }

    std::vector<int> left, right;

    for (size_t i = 0; i < v.size(); ++i) {
        if (v[i] == pivot) continue;
        if (v[i] < pivot) left.push_back(v[i]);
        else right.push_back(v[i]);
    }

    quickSortMedianPivot(left);
    quickSortMedianPivot(right);

    v.clear();
    v.insert(v.end(), left.begin(), left.end());
    v.push_back(pivot);
    v.insert(v.end(), right.begin(), right.end());
}

// This version of quickSort selects a random element as the pivot.
#include <cstdlib>
#include <ctime>
void quickSortRandomPivot(std::vector<int>& v) {
    if (v.size() <= 1) return;

    std::srand(std::time(0));   // srand could also be done by chrono::system_clock::now().time_since_epoch().count()
    size_t randomIndex = std::rand() % v.size();
    int pivot = v[randomIndex];

    std::vector<int> left, right;

    for (size_t i = 0; i < v.size(); ++i) {
        if (i == randomIndex) continue;
        if (v[i] < pivot) left.push_back(v[i]);
        else right.push_back(v[i]);
    }

    quickSortRandomPivot(left);
    quickSortRandomPivot(right);

    v.clear();
    v.insert(v.end(), left.begin(), left.end());
    v.push_back(pivot);
    v.insert(v.end(), right.begin(), right.end());
}

// This version of quickSort uses a ternary partitioning scheme.
// It divides the array into three parts: less than, equal to, and greater than the pivot.
// Credits to https://catalin.francu.com/ for teaching me this algorithm.
void ternaryQuickSort(std::vector<int>& v) {
    if (v.size() <= 1) return;

    int pivot = v[v.size() / 2];
    std::vector<int> left, middle, right;

    for (size_t i = 0; i < v.size(); ++i) {
        if (v[i] < pivot) left.push_back(v[i]);
        else if (v[i] == pivot) middle.push_back(v[i]);
        else right.push_back(v[i]);
    }

    ternaryQuickSort(left);
    ternaryQuickSort(right);

    v.clear();
    v.insert(v.end(), left.begin(), left.end());
    v.insert(v.end(), middle.begin(), middle.end());
    v.insert(v.end(), right.begin(), right.end());
}