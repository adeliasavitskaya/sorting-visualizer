#include "doctest.h"
#include "../src/algorithms/merge_sort.h"
#include "core/sort_step.h"
#include <stdexcept>

TEST_CASE("merge_sort basic") {
    SUBCASE("unsorted array") {
        std::vector<int> arr{3, 2, 1};
        auto steps = merge_sort(arr);
        CHECK(steps.back().array == std::vector<int>{1, 2, 3});
    }
    SUBCASE("already sorted") {
        std::vector<int> arr{1, 2, 3};
        auto steps = merge_sort(arr);
        CHECK(steps.back().array == std::vector<int>{1, 2, 3});
    }
    SUBCASE("reverse sorted") {
        std::vector<int> arr{5, 4, 3, 2, 1};
        auto steps = merge_sort(arr);
        CHECK(steps.back().array == std::vector<int>{1, 2, 3, 4, 5});
    }
    SUBCASE("single element") {
        std::vector<int> arr{1};
        auto steps = merge_sort(arr);
        CHECK(steps.back().array == std::vector<int>{1});
    }
    SUBCASE("duplicate elements") {
        std::vector<int> arr{2, 2, 2};
        auto steps = merge_sort(arr);
        CHECK(steps.back().array == std::vector<int>{2, 2, 2});
    }
}

TEST_CASE("merge_sort steps") {
    SUBCASE("steps not empty") {
        std::vector<int> arr{3, 2, 1};
        auto steps = merge_sort(arr);
        CHECK(!steps.empty());
    }
    SUBCASE("steps contain SPLIT type") {
        std::vector<int> arr{3, 2, 1};
        auto steps = merge_sort(arr);
        CHECK(std::any_of(begin(steps), end(steps),
            [](const SortStep& s) {return s.type == StepType::SPLIT;}));
    }
    SUBCASE("steps contain MERGE type") {
        std::vector<int> arr{3, 2, 1};
        auto steps = merge_sort(arr);
        CHECK(std::any_of(steps.begin(), steps.end(), [](const SortStep& s) {
            return s.type == StepType::MERGE;}));
    }
    SUBCASE("last step is DONE") {
        std::vector<int> arr{3, 2, 1};
        auto steps = merge_sort(arr);
        CHECK(steps.back().type == StepType::DONE);
    }
}

TEST_CASE("merge_sort negative") {
    SUBCASE("empty throws") {
        std::vector<int> arr{};
        CHECK_THROWS_AS(merge_sort(arr), std::invalid_argument);
    }
}