#include <vector>
#include "core/sort_step.h"

/// @brief Создаёт один шаг быстрой сортировки
/// @param array Текущее состояние массива
/// @param l Левая граница активного подмассива
/// @param r Правая граница активного подмассива
/// @param ind_pvt Индекс опорного элемента (pivot)
/// @param lvl Уровень дерева рекурсии (0 — корень)
/// @param type Тип шага (FIND_PIVOT, SWAP, DONE)
/// @return Заполненный объект SortStep
SortStep make_step(const std::vector<int>& array, int l, int r, int first,
    int second, int ind_pvt, int lvl, StepType type) {
    SortStep s;
    s.array = array;
    s.left = l;
    s.right = r;
    s.pivot = ind_pvt;
    s.first = first;
    s.second = second;
    s.level = lvl;
    s.type = type;
    return s;
}

/// @brief Разбивает подмассив [l..r] на две части по схеме Ломуто
/// @details Pivot — правый элемент arr[r]. После выполнения pivot стоит
/// на своей финальной позиции: все элементы слева меньше или равны ему,
/// все элементы справа — больше. Записывает шаг COMPARE при каждом сравнении
/// и шаг SWAP при каждом обмене.
/// @param arr Массив для разбиения (изменяется на месте)
/// @param l Левая граница подмассива
/// @param r Правая граница подмассива (индекс pivot)
/// @param steps Вектор шагов для записи
/// @param lvl Уровень рекурсии
/// @return Финальный индекс pivot после разбиения
int partition(std::vector<int>& arr, int l, int r, std::vector<SortStep>& steps, int lvl) {
    int ind_pvt{r};
    int pvt{arr[ind_pvt]};
    int i{l - 1};

    for (int j{l}; j < r; j++) {
        SortStep cmp = make_step(arr, l, r, i+1, j, ind_pvt, lvl, StepType::COMPARE);
        steps.push_back(cmp);

        if (arr[j] <= pvt) {
            i++;
            std::swap(arr[i], arr[j]);
            if (i != j) {
                SortStep s = make_step(arr, l, r, i, j, ind_pvt, lvl, StepType::SWAP);
                steps.push_back(s);
            }
        }
    }

    std::swap(arr[i+1], arr[ind_pvt]);
    if (i+1 != ind_pvt) {  // не записываем если pivot уже на месте
        SortStep swap_pvt = make_step(arr, l, r, i+1, ind_pvt, ind_pvt, lvl, StepType::SWAP);
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
/// @param lvl Уровень рекурсии
void quick_sort_helper(std::vector<int>& array, std::vector<SortStep>& steps,
    int l, int r, int lvl) {
    if (l >= r) { return; }

    steps.push_back(make_step(array, l, r, r, -1, -1, lvl, StepType::FIND_PIVOT));

    int p = partition(array, l, r, steps, lvl);
    quick_sort_helper(array, steps, l, p-1, lvl+1);
    quick_sort_helper(array, steps, p+1, r, lvl+1);
}

/// @brief Быстрая сортировка — публичный интерфейс
/// @details Возвращает вектор шагов, каждый из которых содержит снимок
/// массива и метаданные для визуализации. Исходный массив не изменяется.
/// @param array Входной массив для сортировки
/// @return Вектор шагов типа SortStep
std::vector<SortStep> quick_sort(const std::vector<int>& array) {
    std::vector<SortStep> steps;
    std::vector arr = array;
    if (array.size() <= 1) {
        steps.push_back(make_step(arr, 0, 0, 0, 0, -1, -1, StepType::DONE));
        return steps;
    }
    quick_sort_helper(arr, steps, 0, arr.size()-1, 0);
    return steps;
}