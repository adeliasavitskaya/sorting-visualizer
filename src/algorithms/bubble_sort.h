#ifndef BUBBLE_SORT_H
#define BUBBLE_SORT_H
#include <vector>
#include "core/sort_step.h"

///@brief Функция сортировка пузырьком
///@param array - массив чисел для сортировки;
///@return вектор шагов SortStep, каждый из которых содержит array и индексы элементов для обмена

std::vector<SortStep> bubble_sort(const std::vector<int>& array);

#endif