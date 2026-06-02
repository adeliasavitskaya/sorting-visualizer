#include "merge_sort.h"
#include "core/sort_step.h"

SortStep make_step(const std::vector<int>& arr, int left, int right, int lvl, StepType type) {
    SortStep step;
    step.array = arr;
    step.left = left;
    step.right = right;
    step.type = type;
    step.level = lvl;
    return step;
}

void merge(std::vector<int>& arr, int left, int mid, int right,
           std::vector<SortStep>& steps, int lvl) {
    std::vector<int> temp;
    int i{left}, j{mid+1};
    while (i <= mid && j <= right) {
        steps.push_back(make_step(arr, i, j, lvl, StepType::MERGE));
        if (arr[i] < arr[j]) {
            temp.push_back(arr[i]);
            i++;
        }
        else {
            temp.push_back(arr[j]);
            j++;
        }
    }
    while (i <= mid) {temp.push_back(arr[i]); i++;}
    while (j <= right) {temp.push_back(arr[j]); j++;}
    for (int k{left}; k<=right; k++) {arr[k] = temp[k-left];}
    steps.push_back(make_step(arr, left, right, lvl, StepType::MERGE));
}

void merge_sort_helper(std::vector<int>& arr, int left, int right,
    std::vector<SortStep>& steps, int lvl) {
    if (left >= right) {return;}

    int mid = (right - left) / 2 + left;
    SortStep step = make_step(arr, left, right, lvl, StepType::SPLIT);
    steps.push_back(step);

    merge_sort_helper(arr, left, mid, steps, lvl+1);
    merge_sort_helper(arr, mid + 1, right, steps, lvl+1);
    merge(arr, left, mid, right, steps, lvl);
}

std::vector<SortStep> merge_sort(const std::vector<int>& array) {
    std::vector<int> arr = array;
    std::vector<SortStep> steps;

    if (arr.size() <= 1) {
        steps.push_back(make_step(arr, 0, 0, 0, StepType::DONE));
        return steps;
    }

    merge_sort_helper(arr, 0, arr.size() - 1, steps, 0);
    return steps;
}

