#ifndef SORTING_VISUALIZER_SORT_STEP_UTILS_H
#define SORTING_VISUALIZER_SORT_STEP_UTILS_H

#include "sort_step.h"

/// @brief Создаёт один шаг сортировки слиянием
/// @param arr Текущее состояние массива
/// @param left Левая граница активного диапазона
/// @param right Правая граница активного диапазона
/// @param first, second активные элементы (сравниваемые или обмениваемые)
/// @param pvt Индекс опорного элемента (-1 если не используется)
/// @param type Тип шага (SPLIT, MERGE, DONE)
/// @param description Текстовое описание шага для отображения пользователю
/// @return Заполненный объект SortStep
inline SortStep make_step(const std::vector<int>& arr=std::vector<int>{},
    int left=-1, int right=-1, int first=-1, int second=-1, int pvt=-1,
    StepType type=StepType::DONE, std::string description="")
{
    SortStep step;
    step.array = arr;
    step.left = left;
    step.right = right;
    step.first = first;
    step.second = second;
    step.pivot = pvt;
    step.type = type;
    step.description = description;
    return step;
}

#endif