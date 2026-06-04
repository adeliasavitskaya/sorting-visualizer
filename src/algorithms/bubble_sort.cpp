#include "bubble_sort.h"

/// @brief Создаёт один шаг сортировки пузырьком
/// @param arr Текущее состояние массива
/// @param first Индекс первого сравниваемого элемента
/// @param second Индекс второго сравниваемого элемента
/// @param type Тип шага (COMPARE, SWAP, DONE)
/// @return Заполненный объект SortStep
SortStep make_step(const std::vector<int>& arr, int first=-1, int second=-1, StepType type=StepType::DONE) {
    SortStep step;
    step.array = arr;
    step.first = first;
    step.second = second;
    step.type = type;
    return step;
}

/// @brief Сортировка пузырьком — публичный интерфейс
/// @details На каждом проходе сравнивает соседние элементы и меняет их местами
/// если левый больше правого. Записывает шаг COMPARE при каждом сравнении
/// и шаг SWAP при каждом обмене. Исходный массив не изменяется.
/// @param array Входной массив для сортировки
/// @return Вектор шагов типа SortStep
std::vector<SortStep> bubble_sort(const std::vector<int>& array) {
    std::vector<int> arr = array;
    int n = arr.size();

    std::vector<SortStep> steps;

    if (n <= 1) {
        SortStep step = make_step(arr);
        step.description = "Массив уже отсортирован";
        steps.push_back(step);
        return steps;
    }

    for (int pass{0}; pass < n; pass++) {
        for (int i{0}; i < n-1; i++) {
            SortStep step = make_step(arr, i, i+1, StepType::COMPARE);
            step.description = "Сравниваем элементы " + std::to_string(arr[i]) + " и " + std::to_string(arr[i+1]);
            steps.push_back(step);
            if (arr[i] > arr[i + 1]) {
                std::swap(arr[i], arr[i+1]);
                SortStep step = make_step(arr, i, i+1, StepType::SWAP);
                step.description = "Меняем местами элементы " + std::to_string(arr[i]) +
                    " и " + std::to_string(arr[i+1]);
                steps.push_back(step);
            }
        }
    }

    return steps;
}