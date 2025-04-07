#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <chrono>
#include <thread>
#include <functional>
#include <iomanip>
#include <map>
#include <cmath>
#include <limits>

// Include your sorting algorithms
#include "../include/quick_sort.h"
#include "../include/merge_sort.h"
#include "../include/radix_sort.h"

// Constants for visualization
const int MAX_DISPLAY_WIDTH = 80;
const int ARRAY_SIZE = 30;  // Size of array to visualize
const int MAX_VALUE = 40;   // Maximum value for random numbers
const int DELAY_MS = 100;   // Delay between frames in milliseconds

// Store the original array for reuse
std::vector<int> originalArray;

// Vector to store the state history
std::vector<std::vector<int>> stateHistory;
std::vector<std::string> stateLabels;

// Clear console screen (platform independent)
void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// Generate a random array for sorting
std::vector<int> generateRandomArray(int size, int maxValue) {
    std::vector<int> array(size);
    srand(static_cast<unsigned>(time(nullptr)));
    for (int i = 0; i < size; i++) {
        array[i] = rand() % (maxValue + 1);
    }
    return array;
}

// Display array as a bar chart
void displayArray(const std::vector<int>& array, const std::string& title = "") {
    clearScreen();
    
    if (!title.empty()) {
        std::cout << "\n" << title << "\n";
    }
    
    int maxVal = *std::max_element(array.begin(), array.end());
    
    // Calculate scaling factor to fit within terminal width
    double scaleFactor = std::min(1.0, static_cast<double>(MAX_DISPLAY_WIDTH) / maxVal);
    
    std::cout << std::string(MAX_DISPLAY_WIDTH + 10, '-') << "\n";
    
    for (size_t i = 0; i < array.size(); i++) {
        int barLength = static_cast<int>(array[i] * scaleFactor);
        std::cout << std::setw(3) << i << " | ";
        std::cout << std::string(barLength, '-');
        std::cout << " " << array[i] << "\n";
    }
    
    std::cout << std::string(MAX_DISPLAY_WIDTH + 10, '-') << "\n";
}
void storeState(const std::vector<int>& array, const std::string& label) {
    stateHistory.push_back(array);
    stateLabels.push_back(label);
}

void visualizerRadixSortBase10(std::vector<int>& v) {
    stateHistory.clear();
    stateLabels.clear();
    storeState(v, "Initial array");
    int maxVal = *std::max_element(v.begin(), v.end());
    for (int exp = 1; maxVal / exp > 0; exp *= 10) {
        std::vector<int> output(v.size());
        std::vector<int> count(10, 0);
        for (size_t i = 0; i < v.size(); i++)
        {    
            count[(v[i] / exp) % 10]++;
            storeState(count, "counting how many numbers have the number in place");
        }
        for (int i = 1; i < 10; i++)
            {
            count[i] += count[i - 1];
            storeState(count, "sorting");
        }
        for (int i = v.size() - 1; i >= 0; i--) {
            output[count[(v[i] / exp) % 10] - 1] = v[i];
            count[(v[i] / exp) % 10]--;
            storeState(output, "sorting");
        }
        v = output;
    }
}

void visualizeMergeSort(std::vector<int>& arr) {
    stateHistory.clear();
    stateLabels.clear();
    storeState(arr, "Initial array");
    
    std::function<void(std::vector<int>&, int, int)> mergeSortImpl = 
        [&](std::vector<int>& arr, int left, int right) {
            if (left < right) {
                // Divide
                int mid = left + (right - left) / 2;
                storeState(arr, "Dividing at position " + std::to_string(mid));
                
                // Conquer
                mergeSortImpl(arr, left, mid);
                mergeSortImpl(arr, mid + 1, right);
                
                // Merge
                std::vector<int> temp(right - left + 1);
                int i = left, j = mid + 1, k = 0;
                
                while (i <= mid && j <= right) {
                    if (arr[i] <= arr[j]) {
                        temp[k++] = arr[i++];
                    } else {
                        temp[k++] = arr[j++];
                    }
                }
                
                while (i <= mid) {
                    temp[k++] = arr[i++];
                }
                
                while (j <= right) {
                    temp[k++] = arr[j++];
                }
                
                // Copy back
                for (i = 0; i < k; i++) {
                    arr[left + i] = temp[i];
                }
                
                storeState(arr, "Merged subarray [" + std::to_string(left) + 
                           "-" + std::to_string(right) + "]");
            }
        };
    
    mergeSortImpl(arr, 0, arr.size() - 1);
    storeState(arr, "Array sorted");
}

// Modified RadixSort with visualization
void visualizeRadixSort(std::vector<int>& arr) {
    stateHistory.clear();
    stateLabels.clear();
    storeState(arr, "Initial array");
    
    // Find max element to know number of digits
    int max = *std::max_element(arr.begin(), arr.end());
    
    // For each digit
    for (int exp = 1; max / exp > 0; exp *= 10) {
        std::vector<int> output(arr.size());
        std::vector<int> count(10, 0);
        
        // Count occurrences of each digit
        for (size_t i = 0; i < arr.size(); i++) {
            count[(arr[i] / exp) % 10]++;
        }
        
        storeState(arr, "Counting digit position " + std::to_string(exp));
        
        // Update count to contain actual position
        for (int i = 1; i < 10; i++) {
            count[i] += count[i - 1];
        }
        
        // Build the output array
        for (int i = arr.size() - 1; i >= 0; i--) {
            output[count[(arr[i] / exp) % 10] - 1] = arr[i];
            count[(arr[i] / exp) % 10]--;
        }
        
        // Copy output to original array
        for (size_t i = 0; i < arr.size(); i++) {
            arr[i] = output[i];
        }
        
        storeState(arr, "After sorting by digit " + std::to_string(exp));
    }
    
    storeState(arr, "Array sorted");
}

// Play back the visualization
void playVisualization() {
    for (size_t i = 0; i < stateHistory.size(); i++) {
        displayArray(stateHistory[i], stateLabels[i]);
        std::this_thread::sleep_for(std::chrono::milliseconds(DELAY_MS));
    }
}

int main() {
    // Generate a random array
    originalArray = generateRandomArray(ARRAY_SIZE, MAX_VALUE);
    
    int choice;
    std::vector<int> workingArray;
    
    while (true) {
        clearScreen();
        std::cout << "=== Sorting Algorithm Visualizer ===" << std::endl;
        std::cout << "1. Visualize Quick Sort" << std::endl;
        std::cout << "2. Visualize Merge Sort" << std::endl;
        std::cout << "3. Visualize Radix Sort" << std::endl;
        std::cout << "4. Generate New Array" << std::endl;
        std::cout << "5. Exit" << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        
        if (choice == 5) break;
        
        switch (choice) {
            case 1:
                workingArray = originalArray;
                // visualizeQuickSort(workingArray);
                playVisualization();
                std::cout << "Press Enter to continue...";
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cin.get();
                break;
                
            case 2:
                workingArray = originalArray;
                visualizeMergeSort(workingArray);
                playVisualization();
                std::cout << "Press Enter to continue...";
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cin.get();
                break;
                
            case 3:
                workingArray = originalArray;
                visualizerRadixSortBase10(workingArray);
                playVisualization();
                std::cout << "Press Enter to continue...";
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cin.get();
                break;
                
            case 4:
                originalArray = generateRandomArray(ARRAY_SIZE, MAX_VALUE);
                std::cout << "New array generated!" << std::endl;
                std::this_thread::sleep_for(std::chrono::seconds(1));
                break;
                
            default:
                std::cout << "Invalid choice! Press Enter to continue...";
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cin.get();
        }
    }
    
    return 0;
}
