#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "../src/algorithms/bubble_sort.h"
#include <stdexcept>

TEST_CASE("bubble_sort basic") {
    SUBCASE("unsorted array") {
        std::vector<int> arr{3, 1, 2};
        auto steps = bubble_sort(arr);
        CHECK(steps.back().array == std::vector<int>{1, 2, 3});
    }
    SUBCASE("already sorted") {
        std::vector<int> arr{1, 2, 3};
        auto steps = bubble_sort(arr);
        CHECK(steps.back().array == std::vector<int>{1, 2, 3});
    }
    SUBCASE("reverse sorted") {
        std::vector<int> arr{3, 2, 1};
        auto steps = bubble_sort(arr);
        CHECK(steps.back().array == std::vector<int>{1, 2, 3});
    }
    SUBCASE("single element") {
        std::vector<int> arr{3};
        auto steps = bubble_sort(arr);
        CHECK(steps.back().array == std::vector<int>{3});
    }
    SUBCASE("duplicate elements") {
        std::vector<int> arr{2, 2, 1};
        auto steps = bubble_sort(arr);
        CHECK(steps.back().array == std::vector<int>{1, 2, 2});
    }
}

TEST_CASE("bubble_sort steps") {
    SUBCASE("steps not empty") {
        std::vector<int> arr{3, 1, 2};
        auto steps = bubble_sort(arr);
        CHECK(!steps.empty());
    }
    SUBCASE("steps contain COMPARE type") {
        std::vector<int> arr{3, 1, 2};
        auto steps = bubble_sort(arr);
        CHECK(std::any_of(steps.begin(), steps.end(), [](const SortStep& s) {
            return s.type == StepType::COMPARE;
        }));
    }
    SUBCASE("steps contain SWAP type") {
        std::vector<int> arr{3, 1, 2};
        auto steps = bubble_sort(arr);
        CHECK(std::any_of(steps.begin(), steps.end(), [](const SortStep& s) {
            return s.type == StepType::SWAP;
        }));
    }
    SUBCASE("last step is DONE") {
        std::vector<int> arr{3, 1, 2};
        auto steps = bubble_sort(arr);
        CHECK(steps.back().type == StepType::DONE);
    }
}

TEST_CASE("bubble_sort negative") {
    SUBCASE("empty throws") {
        std::vector<int> arr{};
        CHECK_THROWS_AS(bubble_sort(arr), std::invalid_argument);
    }
}