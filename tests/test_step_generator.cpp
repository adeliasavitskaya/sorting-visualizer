#include "doctest.h"
#include "core/step_generator.h"

TEST_CASE("generate_steps") {
    std::vector<int> arr = {3, 1, 2};
    std::vector<int> sorted = {1, 2, 3};

    SUBCASE("bubble") {
        auto steps = generate_steps(arr, SortType::BUBBLE);
        CHECK(!steps.empty());
        CHECK(steps.back().array == sorted);
    }
    SUBCASE("merge") {
        auto steps = generate_steps(arr, SortType::MERGE);
        CHECK(!steps.empty());
        CHECK(steps.back().array == sorted);
    }
    SUBCASE("quick") {
        auto steps = generate_steps(arr, SortType::QUICK);
        CHECK(!steps.empty());
        CHECK(steps.back().array == sorted);
    }
}

TEST_CASE("generate_step: invalid type throws") {
    std::vector<int> arr = {3, 1, 2};
    CHECK_THROWS_AS(generate_steps(arr, static_cast<SortType>(99)), std::invalid_argument);
}