#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <functional>
#include "../include/merge_sort.h"
#include "../include/quick_sort.h"
#include "../include/radix_sort.h"
#include "../include/intro_sort.h"
#include "../include/test_utils.h"
#include "../include/shell_sort.h"
#include "../include/tim_sort.h"

std::map<std::string, std::function<void(std::vector<int>&)>> sort_map = {
    {"quickSortHalfPivot", quickSortHalfPivot},
    {"quickSortMedianPivot", quickSortMedianPivot},
    {"quickSortRandomPivot", quickSortRandomPivot},
    {"ternaryQuickSort", ternaryQuickSort},
    {"merge", mergeSort},
    {"radix10", radixSortBase10},
    {"radix16", radixSortBase16},
    {"radix65536", radixSortBase65536},
    {"intro", introSort},
    {"shell", shellsort},
    {"tim", timsort}
};

void printAvailableSorts() {
    std::cout << "Available sorts:\n";
    for (const auto& [name, _] : sort_map) {
        std::cout << name << std::endl;
    }
}

void printArray(const std::vector<int>& v) {
    for (const auto& elem : v) {
        std::cout << elem << " ";
    }
    std::cout << "\n";
}

int main(int argc, char* argv[]) {

    std::srand(std::time(0));

    if (argc == 1) {
        // If no arguments are passed, list the available sorts
        printAvailableSorts();
        return 0;
    }

    std::string command = argv[1];

    if (command == "init") {
        std::ofstream resultFile("results.csv", std::ios::trunc);
        if (!resultFile.is_open()) {
            std::cerr << "Failed to open results.csv\n";
            return 1;
        }
        writeHeader(resultFile);
        std::cout << "Results file initialized.\n";
        return 0;
    }

    if (command == "all") {
        auto tests = readTestConfigs("test_config.csv");
        std::ofstream resultFile("results.csv", std::ios::app);

        if (!resultFile.is_open()) {
            std::cerr << "Failed to open results.csv for appending\n";
            return 1;
        }

        for (const auto& [sortName, sortFunction] : sort_map) {
            for (const auto& test : tests) {
                auto original = generateRandomVector(test.N, test.maxVal);
                std::vector<int> v = original;
                double t = measureTime(sortFunction, v);
                logResult(resultFile, test.name, sortName, test.N, test.maxVal, t, isSorted(v));
            }
        }

        std::cout << "Benchmarking complete for all sorts. See results.csv\n";
        return 0;
    }

    if (sort_map.find(command) == sort_map.end()) {
        std::cerr << "Error: Invalid sorting algorithm. Please choose from the following:\n";
        printAvailableSorts();
        return 1;
    }

    auto tests = readTestConfigs("test_config.csv");
    std::ofstream resultFile("results.csv", std::ios::app);

    if (!resultFile.is_open()) {
        std::cerr << "Failed to open results.csv for appending\n";
        return 1;
    }

    for (const auto& test : tests) {
        auto original = generateRandomVector(test.N, test.maxVal);
        std::vector<int> v = original;
        double t = measureTime(sort_map[command], v);
        logResult(resultFile, test.name, command, test.N, test.maxVal, t, isSorted(v));
    }

    std::cout << "Benchmarking complete. See results.csv\n";
    return 0;
}
