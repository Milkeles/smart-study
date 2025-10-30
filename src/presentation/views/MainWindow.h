/* @file MainWindow.h
 * @brief Main window view of the Smart Study application
 * 
 * This class provides the primary UI container for the application,
 * managing navigation between different views (FlashCards, Pomodoro, etc.)
 * 
 * @version 1.0.0
 * @author Hristo T. Hristov (milkeles)
 * @date Created: 30/10/2025
 * @date Updated: 30/10/2025
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget* parent = nullptr);
private:
    QWidget* centralWidget;
    QVBoxLayout* layout;
    QLabel* titleLabel;
    QPushButton* flashcardsButton;
    QPushButton* pomodoroButton;
};

#endif