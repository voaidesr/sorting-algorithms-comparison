#include "radix_sort.h"
#include <algorithm>

void radixSortBase10(std::vector<int>& v) {
    int maxVal = *std::max_element(v.begin(), v.end());
    for (int exp = 1; maxVal / exp > 0; exp *= 10) {
        std::vector<int> output(v.size());
        int count[10] = {0};

        for (size_t i = 0; i < v.size(); i++)
            count[(v[i] / exp) % 10]++;

        for (int i = 1; i < 10; i++)
            count[i] += count[i - 1];

        for (int i = v.size() - 1; i >= 0; i--) {
            output[count[(v[i] / exp) % 10] - 1] = v[i];
            count[(v[i] / exp) % 10]--;
        }

        v = output;
    }
}

void radixSortBasePow2(std::vector<int>& v, const int exp2) {
    int maxVal = *std::max_element(v.begin(), v.end());
    int base = 1 << exp2;
    for (int exp = 0; (maxVal >> exp) > 0; exp += exp2) {
        std::vector<int> output(v.size());
        int count[base] = {0};

        for (size_t i = 0; i < v.size(); i++)
            count[(v[i] >> exp) & (base - 1)]++;

        for (int i = 1; i < base; i++)
            count[i] += count[i - 1];

        for (int i = v.size() - 1; i >= 0; i--) {
            output[count[(v[i] >> exp) & (base - 1)] - 1] = v[i];
            count[(v[i] >> exp) & (base - 1)]--;
        }

        v = output;
    }
}

void radixSortBase16(std::vector<int>& v) {
    radixSortBasePow2(v, 4);
}

void radixSortBase65536(std::vector<int>& v) {
    radixSortBasePow2(v, 16);
}