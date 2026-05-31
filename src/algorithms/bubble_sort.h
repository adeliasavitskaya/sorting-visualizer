#ifndef BUBBLE_SORT_H
#define BUBBLE_SORT_H
#include <vector>
#include "core/sort_step.h"

///@brief Функция сортировка пузырьком
///@param array - массив чисел для сортировки;
///@return вектор шагов SortStep, каждый из которых содержит array и индексы элементов для обмена

std::vector<SortStep> bubble_sort(const std::vector<int>& array);

///@brief Функция сохраняет параметры для одного шага сортировки
///@param arr - массив чисел для сортировки;
///@param first, second - индексы элементов
///@param type - тип шага
///@return SortStep (один шаг со всеми параметрами)
SortStep make_step(const std::vector<int>& arr, int first=-1, int second=-1, StepType type=StepType::DONE);
#endif