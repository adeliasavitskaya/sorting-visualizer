#ifndef SRC_ALGORITHMS_MERGE_SORT_HPP_
#define SRC_ALGORITHMS_MERGE_SORT_HPP_

#include <vector>
#include "core/sort_step.h"

///@brief Функция сортировка слиянием
///@param array - массив чисел для сортировки
///@return вектор шагов SortStep
std::vector<SortStep> merge_sort(const std::vector<int>& array);

#endif