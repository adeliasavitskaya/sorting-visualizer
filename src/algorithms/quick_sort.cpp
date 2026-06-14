#include <vector>
#include "core/sort_step.h"
#include "core/sort_step_utils.h"
#include <stdexcept>

/// @brief Разбивает подмассив [l..r] на две части по схеме Ломуто
/// @details Pivot — правый элемент arr[r]. После выполнения pivot стоит
/// на своей финальной позиции: все элементы слева меньше или равны ему,
/// все элементы справа — больше. Записывает шаг COMPARE при каждом сравнении
/// и шаг SWAP при каждом обмене.
/// @param arr Массив для разбиения (изменяется на месте)
/// @param l Левая граница подмассива
/// @param r Правая граница подмассива (индекс pivot)
/// @param steps Вектор шагов для записи
/// @return Финальный индекс pivot после разбиения
int partition(std::vector<int>& arr, int l, int r, std::vector<SortStep>& steps) {
    int ind_pvt{r};
    int pvt{arr[ind_pvt]};
    int i{l - 1};

    for (int j{l}; j < r; j++) {
        SortStep cmp = make_step(arr, l, r, i+1, j, ind_pvt, StepType::COMPARE,
            "Сравниваем " + std::to_string(arr[j]) + " с опорным " + std::to_string(pvt));
        steps.push_back(cmp);

        if (arr[j] <= pvt) {
            i++;
            int a{arr[i]}, b{arr[j]};
            std::swap(arr[i], arr[j]);
            if (i != j) {
                SortStep s = make_step(arr, l, r, i, j, ind_pvt, StepType::SWAP,
        "Меняем местами " + std::to_string(a) + " и " + std::to_string(b));
                steps.push_back(s);
            }
        }
    }

    int a{arr[i+1]}, b{arr[ind_pvt]};
    std::swap(arr[i+1], arr[ind_pvt]);
    if (i+1 != ind_pvt) {
        SortStep swap_pvt = make_step(arr, l, r, i+1, ind_pvt, ind_pvt, StepType::SWAP,
            "Опорный " + std::to_string(a) + " встаёт на место " + std::to_string(i+1));
        steps.push_back(swap_pvt);
    }
    ind_pvt = i + 1;
    return ind_pvt;
}

/// @brief Рекурсивный помощник быстрой сортировки
/// @details Записывает шаг FIND_PIVOT, вызывает partition, затем рекурсивно
/// сортирует левую [l..p-1] и правую [p+1..r] части. Pivot исключается —
/// сужение диапазона гарантировано.
/// @param array Массив для сортировки (изменяется на месте)
/// @param steps Вектор шагов для записи
/// @param l Левая граница текущего диапазона
/// @param r Правая граница текущего диапазона
void quick_sort_helper(std::vector<int>& array, std::vector<SortStep>& steps,
    int l, int r) {
    if (l >= r) { return; }

    steps.push_back(make_step(array, l, r, -1, -1, r, StepType::FIND_PIVOT,
        "Выбираем опорный элемент: " + std::to_string(array[r])));

    int p = partition(array, l, r, steps);
    quick_sort_helper(array, steps, l, p-1);
    quick_sort_helper(array, steps, p+1, r);
}

/// @brief Быстрая сортировка — публичный интерфейс
/// @details Возвращает вектор шагов, каждый из которых содержит снимок
/// массива и метаданные для визуализации. Исходный массив не изменяется.
/// @param array Входной массив для сортировки
/// @return Вектор шагов типа SortStep
std::vector<SortStep> quick_sort(const std::vector<int>& array) {
    if (array.empty()) throw std::invalid_argument("Массив пустой");
    std::vector<SortStep> steps;
    std::vector arr = array;
    if (array.size() <= 1) {
        steps.push_back(make_step(arr, -1, -1, -1, -1, -1, StepType::DONE));
        return steps;
    }
    quick_sort_helper(arr, steps, 0, arr.size()-1);
    steps.push_back(make_step(arr, -1, -1, -1, -1, -1, StepType::DONE,
        "Массив отсортирован!"));
    return steps;
}