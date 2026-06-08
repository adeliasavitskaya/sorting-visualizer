#include "app_window.h"
#include <QHBoxLayout>
#include <QVBoxLayout>

AppWindow::AppWindow(QWidget *parent) : QMainWindow(parent) {
    m_startBtn = new QPushButton("Старт", this);
    m_nextBtn  = new QPushButton("Вперёд", this);
    m_prevBtn  = new QPushButton("Назад", this);
    m_algoBox = new QComboBox(this);
    m_algoBox->addItem("Пузырёк");
    m_algoBox->addItem("Слияние");
    m_algoBox->addItem("Быстрая");
    m_timer = new QTimer(this);
    m_visualizer = new QWidget(this);
    m_inputWidget = new ArrayInputWidget(this);
    m_visualizer = new QWidget(this);  // временно, заменим позже

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

    connect(m_startBtn, &QPushButton::clicked, this, &AppWindow::onStartClicked);
    connect(m_nextBtn, &QPushButton::clicked, this, &AppWindow::onNextClicked);
    connect(m_prevBtn,  &QPushButton::clicked, this, &AppWindow::onPrevClicked);

    connect(m_timer, &QTimer::timeout, this, &AppWindow::onTimerTick);
}

void AppWindow::onStartClicked() {
     
}