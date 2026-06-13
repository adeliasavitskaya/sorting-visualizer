#include "merge_sort.h"
#include "core/sort_step.h"

/// @brief Создаёт один шаг сортировки слиянием
/// @param arr Текущее состояние массива
/// @param left Левая граница активного диапазона
/// @param right Правая граница активного диапазона
/// @param first, second сравниваемые элементы
/// @param lvl Уровень дерева рекурсии (0 — корень)
/// @param type Тип шага (SPLIT, MERGE, DONE)
/// @return Заполненный объект SortStep
SortStep make_step(const std::vector<int>& arr, int left, int right,
                   int first, int second, int lvl, StepType type) {
    SortStep step;
    step.array = arr;
    step.left = left;
    step.right = right;
    step.first = first;
    step.second = second;
    step.type = type;
    step.level = lvl;
    return step;
}

/// @brief Сливает два отсортированных подмассива [left..mid] и [mid+1..right]
/// @details Использует вспомогательный буфер temp. Записывает шаг MERGE
/// при каждом сравнении элементов и финальный шаг после копирования.
/// @param arr Массив, подмассивы которого сливаются (изменяется на месте)
/// @param left Левая граница левого подмассива
/// @param mid Правая граница левого подмассива
/// @param right Правая граница правого подмассива
/// @param steps Вектор шагов для записи
/// @param lvl Уровень рекурсии
void merge(std::vector<int>& arr, int left, int mid, int right,
           std::vector<SortStep>& steps, int lvl) {
    std::vector<int> temp;
    int i{left}, j{mid + 1};

    while (i <= mid && j <= right) {
        steps.push_back(make_step(arr, left, right, i, j, lvl, StepType::MERGE));
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

    for (int k{left}; k <= right; k++) { arr[k] = temp[k - left]; }

    steps.push_back(make_step(arr, left, right, -1, -1, lvl, StepType::MERGE));
}

/// @brief Рекурсивный помощник сортировки слиянием
/// @details Делит диапазон пополам (шаг SPLIT), рекурсивно сортирует
///каждую половину, затем сливает их обратно.
/// @param arr Массив для сортировки (изменяется на месте)
/// @param left Левая граница текущего диапазона
/// @param right Правая граница текущего диапазона
/// @param steps Вектор шагов для записи
/// @param lvl Уровень рекурсии
void merge_sort_helper(std::vector<int>& arr, int left, int right,
                       std::vector<SortStep>& steps, int lvl) {
    if (left >= right) { return; }

    int mid = (right - left) / 2 + left;
    steps.push_back(make_step(arr, left, right, left, mid+1, lvl, StepType::SPLIT));

    merge_sort_helper(arr, left, mid, steps, lvl + 1);
    merge_sort_helper(arr, mid + 1, right, steps, lvl + 1);
    merge(arr, left, mid, right, steps, lvl);
}

/// @brief Сортировка слиянием — публичный интерфейс
/// @details Возвращает вектор шагов, каждый из которых содержит снимок
/// массива и данные для визуализации. Исходный массив не изменяется.
/// @param array Входной массив для сортировки
/// @return Вектор шагов типа SortStep
std::vector<SortStep> merge_sort(const std::vector<int>& array) {
    std::vector<int> arr = array;
    std::vector<SortStep> steps;

    if (arr.size() <= 1) {
        steps.push_back(make_step(arr, 0, 0, 0, -1, -1, StepType::DONE));
        return steps;
    }

    merge_sort_helper(arr, 0, arr.size() - 1, steps, 0);
    return steps;
}