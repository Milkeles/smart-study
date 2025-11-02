/**
 * @file MainWindow.cpp
 * @brief Implementation of the MainWindow.h class.
 * 
 * @author Hristo T. Hristov (milkeles)
 * @date Created: 30/10/2025 (dd/mm/yyyy)
 * @date Updated: 30/10/2025 (dd/mm/yyyy)
 */

#include "MainWindow.h"

#include <QFile>

#include "utils/GuiUtils.h"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
    
    centralWidget = new QWidget(this);
    centralWidget->setObjectName("background1");
    
    layout = new QVBoxLayout(centralWidget);
    
    titleLabel = new QLabel("Hello world!", centralWidget);
    titleLabel->setObjectName("titleLabel");
    
    flashcardsButton = new QPushButton("Flash Cards", centralWidget);
    flashcardsButton->setObjectName("PrimaryButton");

    pomodoroButton = new QPushButton("Pomodoro Timer", centralWidget);
    pomodoroButton->setObjectName("PrimaryButton");

    layout->setContentsMargins(20, 20, 20, 20);
    layout->setSpacing(10);
    layout->addWidget(titleLabel, 0, Qt::AlignCenter);
    layout->addWidget(flashcardsButton);
    layout->addWidget(pomodoroButton);
    
    setCentralWidget(centralWidget);
    setWindowTitle("Smart Study");
    resize(800, 600);
}