/* @file MainWindow.cpp
 * @brief Implementation of the MainWindow.h class.
 * 
 * @version 1.0.0
 * @author Hristo T. Hristov (milkeles)
 * @date Created: 30/10/2025 (dd/mm/yyyy)
 * @date Updated: 30/10/2025 (dd/mm/yyyy)
 */

#include "MainWindow.h"

#include <QFile>
#include <QGraphicsDropShadowEffect>

// Move into utility file later.
QGraphicsDropShadowEffect* makeShadow(int blur = 20, QPointF offset = QPointF(0, 4), QColor color = QColor(0,0,0,80)) {
    auto* effect = new QGraphicsDropShadowEffect();
    effect->setBlurRadius(blur);
    effect->setOffset(offset);
    effect->setColor(color);
    return effect;
}

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
    // Load stylesheet
    QFile styleFile("resources/styles/main.qss");
    if (styleFile.open(QFile::ReadOnly)) {
        QString style = QLatin1String(styleFile.readAll());
        setStyleSheet(style);
    }
    
    centralWidget = new QWidget(this);
    layout = new QVBoxLayout(centralWidget);
    
    titleLabel = new QLabel("Hello world!", centralWidget);
    titleLabel->setObjectName("titleLabel");
    
    flashcardsButton = new QPushButton("Flash Cards", centralWidget);
    flashcardsButton->setObjectName("PrimaryButton");
    flashcardsButton->setGraphicsEffect(makeShadow());
    pomodoroButton = new QPushButton("Pomodoro Timer", centralWidget);

    pomodoroButton->setObjectName("PrimaryButton");
    pomodoroButton->setGraphicsEffect(makeShadow());

    layout->setContentsMargins(20, 20, 20, 20);
    layout->setSpacing(10);
    layout->addWidget(titleLabel, 0, Qt::AlignCenter);
    layout->addWidget(flashcardsButton);
    layout->addWidget(pomodoroButton);
    
    setCentralWidget(centralWidget);
    setWindowTitle("Smart Study");
    resize(800, 600);
}