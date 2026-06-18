#include <stdexcept>

#include "algorithms/quick_sort.h"
#include "core/sort_step.h"
#include "doctest.h"

TEST_CASE("quick_sort basic") {
    SUBCASE("unsorted array") {
        std::vector<int> arr{5, 3, 1, 4, 2};
        auto steps = quick_sort(arr);
        CHECK(steps.back().array == std::vector<int>{1, 2, 3, 4, 5});
    }
    SUBCASE("already sorted") {
        std::vector<int> arr{1, 2, 3, 4, 5};
        auto steps = quick_sort(arr);
        CHECK(steps.back().array == std::vector<int>{1, 2, 3, 4, 5});
    }
    SUBCASE("reverse sorted") {
        std::vector<int> arr{5, 4, 3, 2, 1};
        auto steps = quick_sort(arr);
        CHECK(steps.back().array == std::vector<int>{1, 2, 3, 4, 5});
    }
    SUBCASE("single element") {
        std::vector<int> arr{1};
        auto steps = quick_sort(arr);
        CHECK(steps.back().array == std::vector<int>{1});
    }
    SUBCASE("duplicate elements") {
        std::vector<int> arr{2, 2, 1};
        auto steps = quick_sort(arr);
        CHECK(steps.back().array == std::vector<int>{1, 2, 2});
    }
}

TEST_CASE("quick_sort steps") {
    SUBCASE("steps not empty") {
        std::vector<int> arr{5, 3, 1, 4, 2};
        auto steps = quick_sort(arr);
        CHECK(!steps.empty());
    }
    SUBCASE("all steps have valid array size") {
        std::vector<int> arr{5, 3, 1, 4, 2};
        auto steps = quick_sort(arr);
        CHECK(std::all_of(steps.begin(), steps.end(),
                          [&arr](const auto& step) { return step.array.size() == arr.size(); }));
    }
    SUBCASE("steps contain FIND_PIVOT type") {
        std::vector<int> arr{5, 3, 1, 4, 2};
        auto steps = quick_sort(arr);
        CHECK(std::any_of(steps.begin(), steps.end(),
                          [](const SortStep& s) { return s.type == StepType::FIND_PIVOT; }));
    }
    SUBCASE("last step is DONE") {
        std::vector<int> arr{5, 3, 1, 4, 2};
        auto steps = quick_sort(arr);
        CHECK(steps.back().type == StepType::DONE);
    }
}

TEST_CASE("quick_sort negative") {
    SUBCASE("empty throws") {
        std::vector<int> arr{};
        CHECK_THROWS_AS(quick_sort(arr), std::invalid_argument);
    }
}