#include "array_input_widget.h"
#include <QHBoxLayout>
#include <QMessageBox>
#include <sstream>

ArrayInputWidget::ArrayInputWidget(QWidget* parent) : QWidget(parent) {

    m_input = new QLineEdit(this);
    m_input->setPlaceholderText("Введите числа через пробел");

    m_randomBtn = new QPushButton("Случайный массив", this);

    auto* layout = new QHBoxLayout(this);
    layout->addWidget(m_randomBtn);
    layout->addWidget(m_input);

    connect(m_randomBtn, &QPushButton::clicked, this, &ArrayInputWidget::onRandomClicked);
}

bool ArrayInputWidget::validate(const QString& text, std::vector<int>& out) const {
    std::istringstream ss(text.toStdString());
    int n;
    while (ss >> n) {
        out.push_back(n);
        if (out.size() > 20) {return false;}
    }
    if (out.empty()) {return false;}
    return true;
}

std::vector<int> ArrayInputWidget::getArray() const {
    std::vector<int> result;
    validate(m_input->text(), result);
    return result;
}

void ArrayInputWidget::onRandomClicked() {
    std::ostringstream ss;
    for (int i{0}; i < 20; i++) {
        int n{rand() % 100 + 1};
        ss << n << " ";
    }
    m_input -> setText(QString::fromStdString(ss.str()));
}