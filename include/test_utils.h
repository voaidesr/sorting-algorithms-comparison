#ifndef TEST_UTILS_H
#define TEST_UTILS_H

#include <string>
#include <vector>
#include <fstream>
#include <chrono>

struct TestConfig {
    std::string name;
    int N;
    int maxVal;
};

std::vector<TestConfig> readTestConfigs(const std::string& filename);
std::vector<int> generateRandomVector(int N, int maxVal);
bool isSorted(const std::vector<int>& v);

template <typename Func>
double measureTime(Func sort, std::vector<int>& v) {
    auto start = std::chrono::high_resolution_clock::now();
    sort(v);
    auto end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration<double>(end - start).count();
}

void writeHeader(std::ofstream& out);
void logResult(std::ofstream& out, const std::string& testName, const std::string& algorithm,
    int N, int maxVal, double time, bool sorted);

#endif