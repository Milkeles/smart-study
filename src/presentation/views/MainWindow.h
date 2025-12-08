/**
 * @file MainWindow.h
 * @brief Main window view of the Smart Study application
 *
 * This class provides the primary UI container for the application,
 * managing navigation between different views (FlashCards, Pomodoro, etc.)
 *
 * @author Hristo T. Hristov (milkeles)
 * @date Created: 30/10/2025
 * @date Updated: 30/10/2025
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QLabel>
#include <QMainWindow>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>
#include <QListWidget>
#include <QDir>
#include <QDialog>
#include <QTextEdit>
#include <QTextBrowser>
#include <QFile>
#include <QTextStream>
#include <QTreeWidget>
#include <QTreeWidgetItem>



class MainWindow : public QMainWindow {
  Q_OBJECT
public:
  MainWindow(QWidget *parent = nullptr);

  private slots:
    void onTopicSelected(QTreeWidgetItem* item);
    void loadTopics();
    void saveMarkdown();
    void loadMarkdown();
    void createNewFile();
    void switchToEditMode();
    void switchToPreviewMode();


private:

 QString renderMarkdown(const QString &md);
QTextBrowser *markdownPreview;

 QWidget *centralWidget;

 QTreeWidget *topicsTree;

QPushButton *flashcardsButton;
QPushButton *importButton;
QPushButton *settingsButton;
QPushButton *saveButton;
QPushButton *newFileButton; 

QTextEdit *markdownEditor;

QString currentFilePath;

QPushButton *previewModeButton;
QPushButton *editModeButton;

bool isPreviewMode = false;
};

#endif