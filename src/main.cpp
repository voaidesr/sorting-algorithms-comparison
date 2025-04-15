#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <functional>
#include "merge_sort.h"
#include "quick_sort.h"
#include "radix_sort.h"
#include "intro_sort.h"
#include "test_utils.h"

std::map<std::string, std::function<void(std::vector<int>&)>> sort_map = {
    {"quickSortHalfPivot", quickSortHalfPivot},
    {"quickSortMedianPivot", quickSortMedianPivot},
    {"quickSortRandomPivot", quickSortRandomPivot},
    {"ternaryQuickSort", ternaryQuickSort},
    {"merge", mergeSort},
    {"radix10", radixSortBase10},
    {"radix16", radixSortBase16},
    {"radix65536", radixSortBase65536},
    {"intro", introSort}
};

void printArray(const std::vector<int>& v) {
    for (const auto& elem : v) {
        std::cout << elem << " ";
    }
    std::cout << "\n";
}

int main() {
    auto tests = readTestConfigs("test_config.csv");
    std::ofstream resultFile("results.csv");
    writeHeader(resultFile);

    for (const auto& test : tests) {
        auto original = generateRandomVector(test.N, test.maxVal);

        for (const auto& [name, sortFunction] : sort_map) {
            std::vector<int> v = original;
            double t = measureTime(sortFunction, v);
            logResult(resultFile, test.name, name, test.N, test.maxVal, t, isSorted(v));
        }
    }

    std::cout << "Benchmarking complete. See results.csv\n";
    return 0;
}