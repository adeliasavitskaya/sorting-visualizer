#ifndef SRC_ALGORITHMS_QUICK_SORT_HPP_
#define SRC_ALGORITHMS_QUICK_SORT_HPP_

#include <vector>

#include "core/sort_step.h"

/// @brief Быстрая сортировка — публичный интерфейс
/// @details Возвращает вектор шагов, каждый из которых содержит снимок
/// массива и метаданные для визуализации. Исходный массив не изменяется.
/// @param array Входной массив для сортировки
/// @return Вектор шагов типа SortStep
std::vector<SortStep> quick_sort(const std::vector<int>& array);

#endif