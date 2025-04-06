#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <functional>
#include "merge_sort.h"
#include "quick_sort.h"
#include "radix_sort.h"
#include "test_utils.h"

std::map<std::string, std::function<void(std::vector<int>&)>> sort_map = {
    {"quickSortHalfPivot", quickSortHalfPivot},
    {"quickSortMedianPivot", quickSortMedianPivot},
    {"quickSortRandomPivot", quickSortRandomPivot},
    {"ternaryQuickSort", ternaryQuickSort},
    {"merge", mergeSort},
    {"radix10", radixSortBase10},
    {"radix16", radixSortBase16},
    {"radix65536", radixSortBase65536}
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

        {
            std::vector<int> v = original;
            double t = measureTime(mergeSort, v);
            logResult(resultFile, test.name, "MergeSort", test.N, test.maxVal, t);
        }

        {
            std::vector<int> v = original;
            double t = measureTime(quickSortHalfPivot, v);
            logResult(resultFile, test.name, "QuickSortHalfPivot", test.N, test.maxVal, t);
        }

        {
            std::vector<int> v = original;
            double t = measureTime(quickSortMedianPivot, v);
            logResult(resultFile, test.name, "QuickSortMedianPivot", test.N, test.maxVal, t);
        }

        {
            std::vector<int> v = original;
            double t = measureTime(quickSortRandomPivot, v);
            logResult(resultFile, test.name, "QuickSortRandomPIvot", test.N, test.maxVal, t);
        }

        {
            std::vector<int> v = original;
            double t = measureTime(ternaryQuickSort, v);
            logResult(resultFile, test.name, "TernaryQuickSort", test.N, test.maxVal, t);
        }

        {
            std::vector<int> v = original;
            double t = measureTime(radixSortBase10, v);
            logResult(resultFile, test.name, "RadixSortBase10", test.N, test.maxVal, t);
        }

        {
            std::vector<int> v = original;
            double t = measureTime(radixSortBase16, v);
            logResult(resultFile, test.name, "RadixSortBase16", test.N, test.maxVal, t);
        }

        {
            std::vector<int> v = original;
            double t = measureTime(radixSortBase65536, v);
            logResult(resultFile, test.name, "RadixSortBase65536", test.N, test.maxVal, t);
        }
    }

    std::cout << "Benchmarking complete. See results.csv\n";
    return 0;
}