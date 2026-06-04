#include "doctest.h"
#include "algorithms/quick_sort.h"
#include "core/sort_step.h"

TEST_CASE("quick_sort basic") {
    SUBCASE("sorted result is correct") {
        std::vector<int> arr = {5, 3, 1, 4, 2};
        auto steps = quick_sort(arr);
        CHECK(steps.back().array == std::vector<int>{1, 2, 3, 4, 5});
    }

    SUBCASE("already sorted array") {
        std::vector<int> arr = {1, 2, 3, 4, 5};
        auto steps = quick_sort(arr);
        CHECK(steps.back().array == std::vector<int>{1, 2, 3, 4, 5});
    }

    SUBCASE("empty") {
        std::vector<int> arr = {};
        auto steps = quick_sort(arr);
        CHECK(steps.back().array == std::vector<int>{});
    }

    SUBCASE("single element") {
        std::vector<int> arr = {1};
        auto steps = quick_sort(arr);
        CHECK(steps.back().array == std::vector<int>{1});
    }

    SUBCASE("duplicate elements") {
        std::vector<int> arr = {2, 2, 1};
        auto steps = quick_sort(arr);
        CHECK(steps.back().array == std::vector<int>{1, 2, 2});
    }

}

TEST_CASE("all steps have valid array size") {
    // в каждом шаге массив той же длины что входной
    std::vector<int> arr = {5, 3, 1, 4, 2};
    auto steps = quick_sort(arr);
    CHECK(std::all_of(begin(steps), end(steps), [&arr](const auto& step) {
        return step.array.size() == arr.size();
    }));
}