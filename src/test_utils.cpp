#include "test_utils.h"
#include <sstream>
#include <random>
#include <iostream>

// this parses the csv config files and returns a vector of test configurations
std::vector<TestConfig> readTestConfigs(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Could not open test config file: " << filename << "\n";
    }
    std::vector<TestConfig> tests;
    std::string line;

    std::getline(file, line);
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string name, n, max;

        std::getline(ss, name, ',');
        std::getline(ss, n, ',');
        std::getline(ss, max, ',');

        tests.push_back({ name, std::stoi(n), std::stoi(max) });
    }
    return tests;
}

// this generates a vector of N int random values, with maxium value maxVal
std::vector<int> generateRandomVector(int N, int maxVal) {
    std::vector<int> v(N);
    std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> dist(0, maxVal);
    for (int& x : v) x = dist(rng);
    return v;
}

bool isSorted(const std::vector<int>& v) {
    for (size_t i = 1; i < v.size(); ++i)
        if (v[i - 1] > v[i]) return false;
    return true;
}

void writeHeader(std::ofstream& out) {
    out << "testname,algorithm,n,maxvalue,time_s,success\n";
}

void logResult(std::ofstream& out, const std::string& testName, const std::string& algorithm,
               int N, int maxVal, double time, bool sorted) {
    out << testName << "," << algorithm << "," << N << "," << maxVal << "," << time << "," << sorted << "\n";
}
