#include <iostream>
#include <vector>
using namespace std;

template <typename T>
void mergeSort(vector<T>& v) {
    if (v.size() <= 1) return;

    size_t mid = v.size() / 2;
    vector<T> left(v.begin(), v.begin() + mid);
    vector<T> right(v.begin() + mid, v.end());

    mergeSort(left);
    mergeSort(right);

    size_t i = 0, j = 0, k = 0;
    while (i < left.size() && j < right.size()) {
        if (left[i] < right[j])
            v[k++] = left[i++];
        else
            v[k++] = right[j++];
    }
    while (i < left.size()) v[k++] = left[i++];
    while (j < right.size()) v[k++] = right[j++];
}