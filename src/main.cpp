#include <QApplication>
#include "ui/app_window.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    app.setStyleSheet(R"(
        QMainWindow, QWidget {
            background-color: #1e1e2e;
            color: #abb2bf;
            font-family: 'Helvetica Neue', 'Segoe UI', Arial, sans-serif;
            font-size: 13px;
        }

        QPushButton {
            background-color: #2a2a3e;
            color: #abb2bf;
            border: 1px solid #3e3e5e;
            border-radius: 6px;
            padding: 6px 16px;
            min-width: 80px;
        }

        QPushButton:hover {
            background-color: #3a3a5e;
            border-color: #6c8ebf;
            color: #ffffff;
        }

        QPushButton:pressed {
            background-color: #6c8ebf;
            color: #ffffff;
        }

        QLineEdit {
            background-color: #2a2a3e;
            color: #abb2bf;
            border: 1px solid #3e3e5e;
            border-radius: 6px;
            padding: 6px 10px;
        }

        QLineEdit:focus {
            border-color: #6c8ebf;
        }

        QComboBox {
            background-color: #2a2a3e;
            color: #abb2bf;
            border: 1px solid #3e3e5e;
            border-radius: 6px;
            padding: 6px 10px;
        }

        QComboBox:hover {
            border-color: #6c8ebf;
        }

        QComboBox::drop-down {
            border: none;
        }

        QComboBox QAbstractItemView {
            background-color: #2a2a3e;
            color: #abb2bf;
            border: 1px solid #3e3e5e;
            selection-background-color: #3a3a5e;
        }

        QSpinBox {
            background-color: #2a2a3e;
            color: #abb2bf;
            border: 1px solid #3e3e5e;
            border-radius: 6px;
            padding: 6px 10px;
        }

        QSpinBox:focus {
            border-color: #6c8ebf;
        }

        QLabel {
            color: #abb2bf;
            font-size: 13px;
        }
    )");

    AppWindow window;
    window.setWindowTitle("Sorting Visualizer");
    window.resize(800, 600);
    window.show();

    return app.exec();
}