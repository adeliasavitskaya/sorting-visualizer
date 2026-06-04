#ifndef SRC_ALGORITHMS_QUICK_SORT_HPP_
#define SRC_ALGORITHMS_QUICK_SORT_HPP_

#include <vector>
#include "core/sort_step.h"

///@brief Быстрая сортировка c записью параметров для визуализации
///@param array - массив для сортировки
///@return Вектор шагов SortStep, каждый из которых содержит
///состояние массива, индексы pivot и границы подмассива
std::vector<SortStep> quick_sort(const std::vector<int>& array);

#endif