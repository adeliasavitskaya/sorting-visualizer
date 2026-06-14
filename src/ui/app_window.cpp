#include "app_window.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMessageBox>
#include "core/step_generator.h"

AppWindow::AppWindow(QWidget *parent) : QMainWindow(parent) {
    m_startBtn = new QPushButton("Старт", this);
    m_nextBtn  = new QPushButton("Вперёд", this);
    m_prevBtn  = new QPushButton("Назад", this);
    m_algoBox = new QComboBox(this);
    m_algoBox->addItem("Пузырёк");
    m_algoBox->addItem("Слияние");
    m_algoBox->addItem("Быстрая");
    m_timer = new QTimer(this);
    m_visualizer = new SortVisualizer(this);
    m_inputWidget = new ArrayInputWidget(this);

    m_descLabel = new QLabel("", this);
    m_descLabel->setAlignment(Qt::AlignCenter);

    auto central = new QWidget(this);
    setCentralWidget(central);

    auto* btnLayout = new QHBoxLayout();
    btnLayout->addWidget(m_startBtn);
    btnLayout->addWidget(m_prevBtn);
    btnLayout->addWidget(m_nextBtn);

    auto* mainLayout = new QVBoxLayout(central);
    mainLayout->addWidget(m_inputWidget);
    mainLayout->addWidget(m_algoBox);
    mainLayout->addLayout(btnLayout);
    mainLayout->addWidget(m_descLabel);
    mainLayout->addWidget(m_visualizer);

    connect(m_inputWidget, &ArrayInputWidget::arrayReady, this,
        [this](const std::vector<int>&) {resetState();});

    connect(m_startBtn, &QPushButton::clicked, this, &AppWindow::onStartClicked);
    connect(m_nextBtn, &QPushButton::clicked, this, &AppWindow::onNextClicked);
    connect(m_prevBtn,  &QPushButton::clicked, this, &AppWindow::onPrevClicked);

    connect(m_timer, &QTimer::timeout, this, &AppWindow::onTimerTick);

    connect(m_algoBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
        this, &AppWindow::resetState);
}

void AppWindow::onStartClicked() {
    if (m_timer->isActive()) {
        m_timer->stop();
        m_startBtn->setText("Старт");
    }
    else {
        if (m_steps.empty()) {
            auto array = m_inputWidget->getArray();
            if (array.empty()) return;
            int alg_indx = m_algoBox->currentIndex();
            SortType sort_type = static_cast<SortType>(alg_indx);

            try {
                m_steps = generate_steps(array, sort_type);
            } catch (const std::invalid_argument& e) {
                QMessageBox::critical(this, "Ошибка", e.what());
                return;
            }
            m_currentStep=0;
            m_visualizer->setStep(m_steps[m_currentStep]);
        }
        if (!m_steps.empty()) {
            m_timer->start(1000);
            m_startBtn->setText("Пауза");
        }
    }
}

void AppWindow::onNextClicked() {
    if (m_currentStep < (int)m_steps.size() - 1) {
        m_currentStep++;
        m_descLabel->setText(QString::fromStdString(m_steps[m_currentStep].description));
        m_visualizer->setStep(m_steps[m_currentStep]);
    }
}

void AppWindow::onPrevClicked() {
    if (m_currentStep > 0) {
        m_currentStep--;
        m_descLabel->setText(QString::fromStdString(m_steps[m_currentStep].description));
        m_visualizer->setStep(m_steps[m_currentStep]);
    }
}

void AppWindow::onTimerTick() {
    if (m_currentStep < (int)m_steps.size() - 1) {
        m_currentStep++;
        m_descLabel->setText(QString::fromStdString(m_steps[m_currentStep].description));
        m_visualizer->setStep(m_steps[m_currentStep]);
    } else {
        m_timer->stop();
        m_startBtn->setText("Старт");
        m_steps.clear();
        m_currentStep = 0;
    }
}

void AppWindow::resetState() {
    m_timer->stop();
    m_startBtn->setText("Старт");
    m_currentStep = 0;

    auto array = m_inputWidget->getArray();
    if (!array.empty()) {
        int alg_indx = m_algoBox->currentIndex();
        SortType sort_type = static_cast<SortType>(alg_indx);
        try {
            m_steps = generate_steps(array, sort_type);
        } catch (const std::invalid_argument& e) {
            QMessageBox::critical(this, "Ошибка", e.what());
            return;
        }
        m_descLabel->setText(QString::fromStdString(m_steps[m_currentStep].description));
        m_visualizer->setStep(m_steps[0]);
    } else {
        m_steps.clear();
    }
}