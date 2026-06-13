#include "array_input_widget.h"
#include <QHBoxLayout>
#include <sstream>

ArrayInputWidget::ArrayInputWidget(QWidget* parent) : QWidget(parent) {
    m_input = new QLineEdit(this);
    m_input->setPlaceholderText("Введите числа через пробел");

    m_randomBtn = new QPushButton("Случайный массив", this);

    m_sizeSpinBox = new QSpinBox(this);
    m_sizeSpinBox->setRange(1, 30);
    m_sizeSpinBox->setValue(20);

    m_sizeLabel = new QLabel("Размер:", this);

    m_clearBtn = new QPushButton("✕", this);
    m_clearBtn->setFixedWidth(30);

    auto* layout = new QHBoxLayout(this);
    layout->addWidget(m_randomBtn);
    layout->addWidget(m_sizeLabel);
    layout->addWidget(m_sizeSpinBox);
    layout->addWidget(m_input);
    layout->addWidget(m_clearBtn);

    connect(m_input, &QLineEdit::textChanged, this, [this] (const QString& text) {
        std::vector<int> arr;
        if (validate(text, arr)) {
            m_input->setStyleSheet("");
            emit arrayReady(arr);
        }
        else if (!text.isEmpty()) {
            m_input->setStyleSheet("background-color: pink; border: 2px solid red;");

            QTimer::singleShot(400, this, [this]() {
                if (!m_lastValidText.isEmpty()) {
                    m_input->blockSignals(true);
                    m_input->setText(m_lastValidText);
                    m_input->blockSignals(false);
                    m_input->setStyleSheet("");
                }
            });
        }
    });
    connect(m_sizeSpinBox, QOverload<int>::of(&QSpinBox::valueChanged), this,
        [this]() {onRandomClicked();});
    connect(m_randomBtn, &QPushButton::clicked, this, &ArrayInputWidget::onRandomClicked);

    connect(m_clearBtn, &QPushButton::clicked, this, [this]() {
        m_input->clear();
    });
}

bool ArrayInputWidget::validate(const QString& text, std::vector<int>& out) const {
    out.clear();
    std::istringstream ss(text.toStdString());
    int max_count = m_sizeSpinBox->value();
    int n;
    while (ss >> n) {
        out.push_back(n);
        if (out.size() > max_count) {
            return false;
        }
    }

    if (!out.empty() && out.size() <= max_count) {
        const_cast<ArrayInputWidget*>(this)->m_lastValidText = text;
    }

    return !out.empty();
}

std::vector<int> ArrayInputWidget::getArray() const {
    std::vector<int> result;
    validate(m_input->text(), result);
    return result;
}

void ArrayInputWidget::onRandomClicked() {
    int randomCount = m_sizeSpinBox->value();
    std::ostringstream ss;
    for (int i{0}; i < randomCount; i++) {
        int n{rand() % 100 + 1};
        ss << n << " ";
    }
    QString newText = QString::fromStdString(ss.str());

    m_input->blockSignals(true);
    m_input->setText(newText);
    m_input->blockSignals(false);
    m_input->setStyleSheet("");

    m_lastValidText = newText;

    std::vector<int> arr;
    validate(newText, arr);
    emit arrayReady(arr);
}