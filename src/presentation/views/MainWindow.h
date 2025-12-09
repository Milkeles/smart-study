/**
 * @file MainWindow.h
 * @brief Main window view of the Smart Study application
 *
 * This class provides the primary UI container for the application,
 * managing navigation between different views and window management.
 *
 * @author Hristo T. Hristov (milkeles)
 * @date Created: 30/10/2025
 * @date Updated: 02/11/2025
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QHBoxLayout>
#include <QMainWindow>
#include <QMdiArea>

#include "presentation/widgets/Sidebar.h"
#include "presentation/widgets/TimerWidget.h"
#include "presentation/widgets/FlashCardManager.h"

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = nullptr);

private slots:
  void onNoteSelected(const QString &topic, const QString &note);
  void onTimerToggle();
  void onFlashCardsClicked();

private:
  void setupUI();
  void createMockTextWindow(const QString &topic, const QString &note);
  void startFlashcardsSession();

  QWidget *centralWidget;
  QHBoxLayout *mainLayout;

  // Left sidebar
  Sidebar *sidebar;

  // Center - IDE-style MDI area
  QMdiArea *mdiArea;

  // Right panel - Timer
  TimerWidget *timerWidget;

  // Flashcards window
  void createFlashCardWindow();
  FlashCardManager *flashManager; 


};

#endif // MAINWINDOW_H