#include "merge_sort.h"
#include "core/sort_step.h"
#include "core/sort_step_utils.h"
#include <stdexcept>

/// @brief Сливает два отсортированных подмассива [left..mid] и [mid+1..right]
/// @details Использует вспомогательный буфер temp. Записывает шаг MERGE
/// при каждом сравнении элементов и финальный шаг после копирования.
/// @param arr Массив, подмассивы которого сливаются (изменяется на месте)
/// @param left Левая граница левого подмассива
/// @param mid Правая граница левого подмассива
/// @param right Правая граница правого подмассива
/// @param steps Вектор шагов для записи
void merge(std::vector<int>& arr, int left, int mid, int right,
           std::vector<SortStep>& steps) {
    std::vector<int> temp;
    int i{left}, j{mid + 1};

    while (i <= mid && j <= right) {
        steps.push_back(make_step(arr, left, right, i, j,
            /*pvt=*/-1, StepType::MERGE,
            "Сравниваем " + std::to_string(arr[i]) + " и " + std::to_string(arr[j])));
        if (arr[i] < arr[j]) {
            temp.push_back(arr[i]);
            i++;
        } else {
            temp.push_back(arr[j]);
            j++;
        }
    }

    while (i <= mid)  { temp.push_back(arr[i]); i++; }
    while (j <= right) { temp.push_back(arr[j]); j++; }

    for (int k{left}; k <= right; k++) {
        arr[k] = temp[k - left];
        steps.push_back(make_step(arr, left, right, k, -1, -1, StepType::MERGE,
            "Слияние: элемент " + std::to_string(arr[k]) + " на позицию " + std::to_string(k)));
    }
}

/// @brief Рекурсивный помощник сортировки слиянием
/// @details Делит диапазон пополам (шаг SPLIT), рекурсивно сортирует
///каждую половину, затем сливает их обратно.
/// @param arr Массив для сортировки (изменяется на месте)
/// @param left Левая граница текущего диапазона
/// @param right Правая граница текущего диапазона
/// @param steps Вектор шагов для записи
void merge_sort_helper(std::vector<int>& arr, int left, int right,
                       std::vector<SortStep>& steps) {
    if (left >= right) { return; }

    int mid = (right - left) / 2 + left;
    steps.push_back(make_step(arr, left, right, left, mid+1,
        /*pvt=*/-1, StepType::SPLIT,
        "Делим массив на две части"));

    merge_sort_helper(arr, left, mid, steps);
    merge_sort_helper(arr, mid + 1, right, steps);
    merge(arr, left, mid, right, steps);
}

/// @brief Сортировка слиянием — публичный интерфейс
/// @details Возвращает вектор шагов, каждый из которых содержит снимок
/// массива и данные для визуализации. Исходный массив не изменяется.
/// @param array Входной массив для сортировки
/// @return Вектор шагов типа SortStep
std::vector<SortStep> merge_sort(const std::vector<int>& array) {
    if (array.empty()) throw std::invalid_argument("Массив пустой");
    std::vector<int> arr = array;
    std::vector<SortStep> steps;

    if (arr.size() <= 1) {
        steps.push_back(make_step(arr, -1, -1, -1, -1, -1, StepType::DONE));
        return steps;
    }

    merge_sort_helper(arr, 0, arr.size() - 1, steps);
    steps.push_back(make_step(arr, -1, -1, -1, -1, -1, StepType::DONE,
        "Массив отсортирован!"));
    return steps;
}