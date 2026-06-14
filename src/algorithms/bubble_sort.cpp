#include "bubble_sort.h"
#include "core/sort_step_utils.h"
#include <stdexcept>

/// @brief Сортировка пузырьком — публичный интерфейс
/// @details На каждом проходе сравнивает соседние элементы и меняет их местами
/// если левый больше правого. Записывает шаг COMPARE при каждом сравнении
/// и шаг SWAP при каждом обмене. Исходный массив не изменяется.
/// @param array Входной массив для сортировки
/// @return Вектор шагов типа SortStep
std::vector<SortStep> bubble_sort(const std::vector<int>& array) {
    if (array.empty()) throw std::invalid_argument("Массив не может быть пустым");
    std::vector<int> arr = array;
    int n = arr.size();

    std::vector<SortStep> steps;

    if (n <= 1) {
        steps.push_back(make_step(arr));
        return steps;
    }

    for (int i{0}; i < n; i++) {
        bool swaped{false};
        for (int j{0}; j < n-1; j++) {
            steps.push_back(make_step(arr, -1, -1, j, j+1, -1, StepType::COMPARE,
                "Сравниваем " + std::to_string(arr[j]) + " и " + std::to_string(arr[j+1])));
            if (arr[j] > arr[j+1]) {
                int a{arr[j]}, b{arr[j+1]};
                std::swap(arr[j], arr[j+1]);
                steps.push_back(make_step(arr, -1, -1, j, j+1, -1, StepType::SWAP,
                    "Меняем местами " + std::to_string(a) + " и " + std::to_string(b)));
                swaped = true;
            }
        }
        if (!swaped) break;
    }
    steps.push_back(make_step(arr, -1, -1, -1, -1, -1, StepType::DONE,
        "Массив отсортирован!"));
    return steps;
}