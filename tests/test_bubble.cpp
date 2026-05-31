#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "../src/algorithms/bubble_sort.h"

TEST_CASE("bubble_sort just_array") {
    std::vector<int> arr{3, 1, 2};
    std::vector<SortStep> sorted = bubble_sort(arr);
    CHECK(sorted.back().array == std::vector<int>{1, 2, 3});
}

TEST_CASE("bubble_sort already_sorted") {
    std::vector<int> arr{1, 2, 3};
    std::vector<SortStep> sorted = bubble_sort(arr);
    CHECK(sorted.back().array == std::vector<int>{1, 2, 3});
}


TEST_CASE("bubble_sort one_elem") {
    std::vector<int> arr{3};
    std::vector<SortStep> sorted = bubble_sort(arr);
    CHECK(sorted.back().array == std::vector<int>{3});
}

TEST_CASE("buble_sort empty") {
    std::vector<int> arr{};
    std::vector<SortStep> sorted = bubble_sort(arr);
    CHECK(sorted.back().array == std::vector<int>{});
}
