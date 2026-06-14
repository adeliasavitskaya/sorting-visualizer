#include "sort_visualizer.h"
#include <QPainter>
#include <algorithm>

SortVisualizer::SortVisualizer(QWidget* parent) : QWidget(parent) {
    setMinimumSize(400, 300);
}

void SortVisualizer::setStep(const SortStep& step) {
    if (m_step.array.empty() || m_step.array.size() != step.array.size()) {
        m_maxVal = *std::max_element(step.array.begin(), step.array.end());
    }
    m_step = step;
    update();
}

void SortVisualizer::paintEvent(QPaintEvent* event) {
    if (m_step.array.empty()) return;
    if (m_maxVal == 0) return;

    QPainter painter(this);
    int n = m_step.array.size();
    int barWidth{width() / n};
    int bottomPadding{20};

    if (m_step.left >= 0 && m_step.right >= 0) {
        int x1 = m_step.left * barWidth;
        int x2 = (m_step.right + 1) * barWidth;
        painter.fillRect(x1, 0, x2 - x1, height() - bottomPadding,
                         QColor(200, 200, 255, 100));
    }

    for (int i{0}; i < n; i++) {
        int barHeight = (double)(height() - bottomPadding) * m_step.array[i] / m_maxVal;
        int x = i * barWidth;
        int y = height() - bottomPadding - barHeight;
        int padding{4};

        QColor color{Qt::blue};
        bool highlight{false};

        if (m_step.type == StepType::MERGE || m_step.type == StepType::SPLIT) {
            int mid = (m_step.left + m_step.right) / 2;
            if (i >= m_step.left && i <= mid)
                color = QColor(150, 100, 255);  // фиолетовый — левая
            if (i > mid && i <= m_step.right)
                color = QColor(255, 150, 50);   // оранжевый — правая
        }

        if (m_step.pivot >= 0 && i == m_step.pivot)
            color = Qt::green;

        if (m_step.type == StepType::SWAP) {
            if (i == m_step.first || i == m_step.second)
                color = Qt::red;
        }

        if (m_step.type == StepType::MERGE &&
            m_step.first >= 0 && m_step.second == -1 && i == m_step.first) {
            color = Qt::red;
        }

        if (m_step.type != StepType::SWAP &&
            !(m_step.type == StepType::MERGE && m_step.second == -1)) {
            if ((m_step.first >= 0 && i == m_step.first) ||
                (m_step.second >= 0 && i == m_step.second)) {
                highlight = true;
            }
        }

        if (m_step.type == StepType::DONE) color = Qt::blue;

        painter.setBrush(color);
        painter.setPen(highlight ? QPen(Qt::black, 2) : Qt::NoPen);
        painter.drawRect(x + padding + 1, y + 1,
                         barWidth - padding * 2 - 2, barHeight - 2);

        painter.setPen(Qt::black);
        painter.drawText(x + padding, height() - 5, QString::number(m_step.array[i]));
    }
}