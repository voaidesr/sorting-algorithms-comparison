#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <functional>
#include "merge_sort.h"
#include "quick_sort.h"

std::map<std::string, std::function<void(std::vector<int>&)>> sort_map = {
    {"quickSortHalfPivot", quickSortHalfPivot},
    {"quickSortMedianPivot", quickSortMedianPivot},
    {"quickSortRandomPivot", quickSortRandomPivot},
    {"ternaryQuickSort", ternaryQuickSort},
    {"merge", mergeSort}
};

void printArray(const std::vector<int>& v) {
    for (const auto& elem : v) {
        std::cout << elem << " ";
    }
    std::cout << "\n";
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: ./bin/main <sort_name>\n";
        return 1;
    }

    std::string sort_name = argv[1];
    std::vector<int> v = {5, 2, 9, 1, 5, 6};

    std::cout << "Original array:\n";
    printArray(v);

    if (sort_map.find(sort_name) == sort_map.end()) {
        std::cerr << "Invalid sort name. Available options are:\n";
        for (const auto &[name, _] : sort_map) {
            std::cout << "[+] " << name << "\n";
        }
        return 1;
    }

    sort_map[sort_name](v);

    std::cout << "Sorted array:\n";
    printArray(v);

    return 0;
}