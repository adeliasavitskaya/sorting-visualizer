#include "sort_visualizer.h"
#include <QPainter>
#include <algorithm>


SortVisualizer::SortVisualizer(QWidget* parent) : QWidget(parent) {
    setMinimumSize(400, 300);
}

void SortVisualizer::setStep(const SortStep& step) {
    m_step = step;
    update();
}


void SortVisualizer::paintEvent(QPaintEvent* event) {
    if (m_step.array.empty()) return;

    QPainter painter(this);
    int n = m_step.array.size();
    int maxVal{*std::max_element(begin(m_step.array), end(m_step.array))};

    int barWidth{width()/n};
    for (int i{0}; i < n; i++) {
        int barHeight = (double)height() * m_step.array[i] / maxVal;
        int x = i * barWidth;
        int y = height() - barHeight;

        int padding{4};

        painter.setBrush(Qt::blue);
        painter.drawRect(x + padding, y, barWidth - padding * 2, barHeight);
    }

}
