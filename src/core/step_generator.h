#ifndef STEP_GENERATOR_H
#define STEP_GENERATOR_H

#include <vector>
#include "core/sort_step.h"

/// @brief Делегирует вызов нужному алгоритму в зависимости от типа
/// Исходный массив не изменяется
/// @param array -  входной массив для сортировки
/// @param type - тип сортиировки
/// @return вектор шагов типа SortStep для визуализации
/// @throws std::invalid_argument если передан неизвестный тип сортировки
std::vector<SortStep> generate_steps(const std::vector<int>& array, SortType type);

#endif