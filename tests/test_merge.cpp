#include "doctest.h"
#include "../src/algorithms/merge_sort.h"
#include "core/sort_step.h"

TEST_CASE("merge just_array") {
    std::vector<int> arr = {3, 2, 1};
    std::vector<SortStep> steps = merge_sort(arr);
    CHECK(steps.back().array == std::vector<int>{1, 2, 3});
    CHECK(std::any_of(steps.begin(), steps.end(), [](const SortStep& s) {
        return s.type == StepType::SPLIT;
    }));
    CHECK(std::any_of(steps.begin(), steps.end(), [](const SortStep& s) {
        return s.type == StepType::MERGE;
    }));
}

TEST_CASE("merge one_elem") {
    std::vector<int> arr = {1};
    std::vector<SortStep> steps = merge_sort(arr);
    CHECK(steps.back().array == std::vector<int>{1});
}

TEST_CASE("merge empty") {
    std::vector<int> arr = {};
    std::vector<SortStep> steps = merge_sort(arr);
    CHECK(steps.back().array == std::vector<int>{});
}

TEST_CASE("merge simillar") {
    std::vector<int> arr = {2, 2, 2};
    std::vector<SortStep> steps = merge_sort(arr);
    CHECK(steps.back().array == std::vector<int>{2, 2, 2});
}

TEST_CASE("merge first_split") {
    std::vector<int> arr{7, 5, 3, 8};
    std::vector <SortStep> steps = merge_sort(arr);
    auto it = std::find_if(steps.begin(), steps.end(), [](const SortStep& s) {
        return s.type == StepType::SPLIT;
    });
    CHECK(it -> level == 0);
}