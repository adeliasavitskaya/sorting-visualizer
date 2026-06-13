#include "app_window.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
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
    mainLayout->addWidget(m_visualizer);

    connect(m_inputWidget, &ArrayInputWidget::arrayReady, this, &AppWindow::onArrayReady);

    connect(m_startBtn, &QPushButton::clicked, this, &AppWindow::onStartClicked);
    connect(m_nextBtn, &QPushButton::clicked, this, &AppWindow::onNextClicked);
    connect(m_prevBtn,  &QPushButton::clicked, this, &AppWindow::onPrevClicked);

    connect(m_timer, &QTimer::timeout, this, &AppWindow::onTimerTick);
}

void AppWindow::onArrayReady(const std::vector<int>& array) {
    SortStep step;
    step.array = array;
    m_visualizer->setStep(step);
}

void AppWindow::onStartClicked() {
    auto array = m_inputWidget->getArray();
    if (array.empty()) return;
    int alg_indx = m_algoBox->currentIndex();
    SortType sort_type = static_cast<SortType>(alg_indx);

    m_steps = generate_steps(array, sort_type);
    m_currentStep=0;
    m_visualizer->setStep(m_steps[m_currentStep]);
    m_timer->start(500);
}

void AppWindow::onNextClicked() {
    if (m_currentStep < (int)m_steps.size() - 1) {
        m_currentStep++;
        m_visualizer->setStep(m_steps[m_currentStep]);
    }
}

void AppWindow::onPrevClicked() {
    if (m_currentStep > 0) {
        m_currentStep--;
        m_visualizer->setStep(m_steps[m_currentStep]);
    }
}

void AppWindow::onTimerTick() {
    if (m_currentStep < (int)m_steps.size() - 1) {
        m_currentStep++;
        m_visualizer->setStep(m_steps[m_currentStep]);
    } else {
        m_timer->stop();
    }
}