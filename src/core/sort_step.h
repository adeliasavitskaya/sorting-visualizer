#ifndef SORT_STEP_H
#define SORT_STEP_H

#include <vector>
#include <string>

enum class StepType {
    COMPARE,
    SWAP,
    FIND_PIVOT,
    MERGE,
    SPLIT,
    DONE
};

struct SortStep {
    std::vector <int> array;
    int first{-1};
    int second{-1};

    int left{-1};
    int right{-1};
    int level{-1};
    StepType type{StepType::DONE};

    std::string description;
};

#endif