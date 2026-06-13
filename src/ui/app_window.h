#ifndef APP_WINDOW_H
#define APP_WINDOW_H

#include <QMainWindow>
#include <QComboBox>
#include <QPushButton>
#include <QTimer>
#include "array_input_widget.h"
#include "sort_visualizer.h"
#include "core/sort_step.h"

/// @brief Главное окно приложения
/// @details Содержит виджет ввода массива, выбор алгоритма, кнопки управления
/// и визуализатор. Координирует взаимодействие между всеми компонентами.
class AppWindow : public QMainWindow {
    Q_OBJECT

public:
    /// @brief Конструктор главного окна
    /// @param parent Родительский виджет (nullptr для корневого)
    explicit AppWindow(QWidget* parent = nullptr);

private slots:
    ///@brief Слот рисует массив после ввода пользователем
    void onArrayReady(const std::vector<int>& array);
    
    /// @brief Слот генерирует шаги и запускает автоматический проход
    void onStartClicked();

    /// @brief Слот переходит к следующему шагу
    void onNextClicked();

    /// @brief Слот возвращается к предыдущему шагу
    void onPrevClicked();

    /// @brief Слот срабатывает по таймеру, показывает следующий шаг
    void onTimerTick();

private:
    ArrayInputWidget* m_inputWidget; ///< Виджет ввода массива

    SortVisualizer* m_visualizer;  ///< Виджет отрисовки шагов

    QComboBox* m_algoBox;     ///< Выпадающий список алгоритмов
    QPushButton* m_startBtn;    ///< Кнопка запуска автопрохода
    QPushButton* m_nextBtn;     ///< Кнопка следующего шага
    QPushButton* m_prevBtn;     ///< Кнопка предыдущего шага
    QTimer* m_timer;       ///< Таймер для автоматического прохода

    std::vector<SortStep> m_steps;   ///< Все шаги текущей сортировки
    int m_currentStep{0};            ///< Индекс текущего шага
};

#endif