#include "bubble_sort.h"

#include <stdexcept>

#include "core/sort_step_utils.h"

std::vector<SortStep> bubble_sort(const std::vector<int>& array) {
    if (array.empty()) throw std::invalid_argument("Array cannot be empty");
    std::vector<int> arr = array;
    int n = arr.size();

    std::vector<SortStep> steps;

    if (n <= 1) {
        steps.push_back(make_step(arr));
        return steps;
    }

    for (int i{0}; i < n; i++) {
        bool swaped{false};
        for (int j{0}; j < n - 1; j++) {
            steps.push_back(make_step(
                arr, -1, -1, j, j + 1, -1, StepType::COMPARE,
                "Comparing " + std::to_string(arr[j]) + " and " + std::to_string(arr[j + 1])));
            if (arr[j] > arr[j + 1]) {
                int a{arr[j]}, b{arr[j + 1]};
                std::swap(arr[j], arr[j + 1]);
                steps.push_back(
                    make_step(arr, -1, -1, j, j + 1, -1, StepType::SWAP,
                              "Swapping " + std::to_string(a) + " and " + std::to_string(b)));
                swaped = true;
            }
        }
        if (!swaped) break;
    }
    steps.push_back(make_step(arr, -1, -1, -1, -1, -1, StepType::DONE, "Array sorted!"));
    return steps;
}