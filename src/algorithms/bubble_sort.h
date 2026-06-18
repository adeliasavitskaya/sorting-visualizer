#ifndef BUBBLE_SORT_H
#define BUBBLE_SORT_H
#include <vector>

#include "core/sort_step.h"

/// @brief Сортировка пузырьком — публичный интерфейс
/// @details На каждом проходе сравнивает соседние элементы и меняет их местами
/// если левый больше правого. Записывает шаг COMPARE при каждом сравнении
/// и шаг SWAP при каждом обмене. Исходный массив не изменяется.
/// @param array Входной массив для сортировки
/// @return Вектор шагов типа SortStep
std::vector<SortStep> bubble_sort(const std::vector<int>& array);

#endif