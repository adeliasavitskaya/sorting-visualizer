#ifndef ARRAY_INPUT_WIDGET_H
#define ARRAY_INPUT_WIDGET_H

#include <QWidget>
#include <QTimer>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QSpinBox>
#include <vector>

/// @brief Виджет ввода массива для визуализатора сортировок
/// @details Позволяет пользователю ввести числа через пробел или сгенерировать
/// случайный массив. Проверяет корректность ввода и отправляет сигнал
/// arrayReady когда массив валидный. Максимальная длина массива — 20 элементов.
class ArrayInputWidget : public QWidget {
    Q_OBJECT

public:
    /// @brief Конструктор виджета
    /// @param parent Родительский виджет (nullptr для корневого)
    explicit ArrayInputWidget(QWidget* parent = nullptr);

    /// @brief Возвращает текущий массив из поля ввода
    /// Если ввод некорректный — возвращает пустой вектор.
    /// @return Вектор целых чисел или пустой вектор при ошибке
    std::vector<int> getArray() const;

    signals:
        /// @brief Сигнал — массив введён корректно и готов к сортировке
            /// @param array Валидный массив целых чисел
        void arrayReady(const std::vector<int>& array);

private slots:
    /// @brief Слот — генерирует случайный массив и вставляет в поле ввода
    void onRandomClicked();

private:
    QLineEdit*   m_input;      ///< Поле ввода чисел через пробел
    QPushButton* m_randomBtn;  ///< Кнопка генерации случайного массива
    QSpinBox* m_sizeSpinBox;   /// < СпинБокс для выбора размера массива
    QString m_lastValidText; /// < Последний валидный текст
    QLabel* m_sizeLabel; /// < Лабл для надписи "Размер:"
    QPushButton* m_clearBtn; /// < Кнопка для очистки поля с числами

    /// @brief Проверяет строку ввода и парсит числа
    /// @details Разбивает строку по пробелам, проверяет что каждый элемент
    /// целое число, и что длина массива не превышает 20 элементов.
    /// @param text Строка из поля ввода
    /// @param out Вектор куда записываются числа при успехе
    /// @return true если ввод корректный, false если есть ошибка
    bool validate(const QString& text, std::vector<int>& out) const;
};

#endif