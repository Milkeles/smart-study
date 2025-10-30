/* @file MainWindow.cpp
 * @brief Implementation of the MainWindow.h class.
 * 
 * @author Hristo T. Hristov (milkeles)
 * @date Created: 30/10/2025 (dd/mm/yyyy)
 * @date Updated: 30/10/2025 (dd/mm/yyyy)
 */

#include "MainWindow.h"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
    centralWidget = new QWidget(this);
    layout = new QVBoxLayout(centralWidget);
    
    titleLabel = new QLabel("Smart Study", centralWidget);
    titleLabel->setStyleSheet("font-size: 28px; color: #212529;");
    
    flashcardsButton = new QPushButton("Flash Cards", centralWidget);
    pomodoroButton = new QPushButton("Pomodoro Timer", centralWidget);
    
    // Example buttons, remove later.
    layout->addWidget(titleLabel, 0, Qt::AlignCenter);
    layout->addWidget(flashcardsButton);
    layout->addWidget(pomodoroButton);
    
    setCentralWidget(centralWidget);
    setWindowTitle("Smart Study");
    resize(800, 600);
}