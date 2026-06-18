#ifndef SORT_STEP_H
#define SORT_STEP_H

#include <vector>

/// @brief Тип алгоритма сортировки
enum class SortType { BUBBLE, MERGE, QUICK };

/// @brief Тип шага визуализации
enum class StepType { COMPARE, SWAP, MERGE, SPLIT, FIND_PIVOT, DONE };

/// @brief Один шаг сортировки для визуализации
struct SortStep {
    std::vector<int> array;         ///< Снимок массива на текущем шаге
    int first{-1};                  ///< Индекс первого активного элемента
    int second{-1};                 ///< Индекс второго активного элемента
    int left{-1};                   ///< Левая граница активного диапазона
    int right{-1};                  ///< Правая граница активного диапазона
    int pivot{-1};                  ///< Индекс опорного элемента
    StepType type{StepType::DONE};  ///< Тип текущего шага
    std::string description;        ///< Текстовое описание шага
};

#endif