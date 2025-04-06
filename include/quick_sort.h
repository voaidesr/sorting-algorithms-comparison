#ifndef QUICK_SORT_H
#define QUICK_SORT_H

#include <vector>

void quickSortHalfPivot(std::vector<int>& v);
void quickSortMedianPivot(std::vector<int>& v);
void quickSortRandomPivot(std::vector<int>& v);
void ternaryQuickSort(std::vector<int>& v);

#endif // QUICK_SORT_H