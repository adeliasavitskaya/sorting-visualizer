#include <stdexcept>
#include "core/sort_step.h"
#include "algorithms/bubble_sort.h"
#include "algorithms/merge_sort.h"
#include "algorithms/quick_sort.h"

std::vector<SortStep> generate_steps(const std::vector<int>& array, SortType type) {
    switch (type) {
        case SortType::BUBBLE:
            return bubble_sort(array);
        case SortType::MERGE:
            return merge_sort(array);
        case SortType::QUICK:
            return quick_sort(array);
        default:
            throw std::invalid_argument("Invalid sort type");
    }
}