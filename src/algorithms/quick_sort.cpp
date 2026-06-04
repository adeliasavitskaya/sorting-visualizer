#include <vector>
#include "core/sort_step.h"

/// @brief Задаёт параметры одного шага сортировки
/// @param array Состояние массива на текущем шаге
/// @param l Левая граница подмассива
/// @param r Правая граница подмассива
/// @param ind_pvt Индекс опорного элемента
/// @param lvl Уровень дерева рекурсии
/// @param type Тип шага
/// @return Один шаг типа SortStep
SortStep make_step(const std::vector<int>& array, int l, int r, int ind_pvt, int lvl, StepType type) {
    SortStep s;
    s.array = array;
    s.left = l;
    s.right = r;
    s.pivot = ind_pvt;
    s.level = lvl;
    s.type = type;
    return s;
}

/// @brief Разбивает подмассив на две части относительно pivot
/// @param arr Массив для разбиения
/// @param l Левая граница
/// @param r Правая граница
/// @param steps Вектор шагов для записи
/// @param lvl Уровень рекурсии
/// @return Финальный индекс границы разбиения
int partition(std::vector<int>& arr, int l, int r, std::vector<SortStep>& steps, int lvl) {
    int ind_pvt{r};
    int pvt{arr[ind_pvt]};
    int i{l - 1};

    for (int j{l}; j < r; j++) {
        if (arr[j] <= pvt) {
            i++;
            std::swap(arr[i], arr[j]);
            steps.push_back(make_step(arr, i, j, ind_pvt, lvl, StepType::SWAP));
        }
    }
    std::swap(arr[i+1], arr[ind_pvt]);
    steps.push_back(make_step(arr, i+1, r, ind_pvt, lvl, StepType::SWAP));
    ind_pvt = i + 1;
    return ind_pvt;
}


/// @brief Рекурсивный помощник быстрой сортировки
/// @param array Массив для сортировки
/// @param steps Вектор шагов для записи
/// @param l Левая граница
/// @param r Правая граница
/// @param lvl Уровень рекурсии
void quick_sort_helper(std::vector<int>& array, std::vector<SortStep>& steps,
    int l, int r, int lvl) {
    if (l >= r) {return;}

    steps.push_back(make_step(array, l, r, r, lvl, StepType::FIND_PIVOT));

    int p = partition(array, l, r, steps, lvl);
    quick_sort_helper(array, steps, l, p-1, lvl+1);
    quick_sort_helper(array, steps, p+1, r, lvl+1);
}

std::vector<SortStep> quick_sort(const std::vector<int>& array) {
    std::vector<SortStep> steps;
    std::vector arr = array;
    if (array.size() <= 1) {
        steps.push_back(make_step(arr, 0, 0, 0, 0, StepType::DONE));
        return steps;
    }
    quick_sort_helper(arr, steps, 0, arr.size()-1, 0);
    return steps;
}