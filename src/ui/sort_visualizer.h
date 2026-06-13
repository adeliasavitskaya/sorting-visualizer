#ifndef SORT_VISUALIZER_H
#define SORT_VISUALIZER_H

#include <QWidget>
#include "core/sort_step.h"

class SortVisualizer: public QWidget {
    Q_OBJECT

public:
    explicit SortVisualizer(QWidget* parent = nullptr);

    ///@brief Устанавливает текущий шаг для отрисовки
    ///@param step Шаг сортировки со всеми данными
    void setStep(const SortStep& step);

protected:
    /// @brief Отрисовывает текущий шаг сортировки в виде столбиков
    /// @details Высота каждого столбика пропорциональна значению элемента,
    /// сравниваемые элементы выделяются цветом
    /// @param event Событие перерисовки от Qt (не используется напрямую)
    void paintEvent(QPaintEvent* event);

private:
    SortStep m_step;  /// < текущий шаг для отображения
};

#endif