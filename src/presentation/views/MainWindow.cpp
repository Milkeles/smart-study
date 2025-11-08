/**
 * @file MainWindow.cpp
 * @brief Implementation of the MainWindow class.
 *
 * @author Hristo T. Hristov (milkeles)
 * @date Created: 30/10/2025 (dd/mm/yyyy)
 * @date Updated: 02/11/2025 (dd/mm/yyyy)
 */

#include "presentation/views/MainWindow.h"

#include <QMdiSubWindow>
#include <QTextEdit>
#include <QApplication>
#include <QBrush>
#include <QColor>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setupUI();

    // Connect signals from sidebar and timer
    connect(sidebar, &Sidebar::noteSelected,
            this, &MainWindow::onNoteSelected);
    connect(sidebar, &Sidebar::flashCardsClicked,
            this, &MainWindow::onFlashCardsClicked);
    connect(timerWidget, &TimerWidget::playClicked,
            this, &MainWindow::onTimerToggle);

    // Demo: initial windows
    createMockTextWindow("Quantum Physics", "Introduction");
    createMockTextWindow("C++ Programming", "Qt Basics");
}

void MainWindow::setupUI() {
    centralWidget = new QWidget(this);
    centralWidget->setObjectName("background1");

    mainLayout = new QHBoxLayout(centralWidget);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);

    // Left: Sidebar
    sidebar = new Sidebar(centralWidget);
    sidebar->setFixedWidth(280);
    sidebar->setObjectName("background2");
    mainLayout->addWidget(sidebar);

    // Center: MDI Document Area
    mdiArea = new QMdiArea(centralWidget);
    mdiArea->setObjectName("background1");
    mdiArea->setViewMode(QMdiArea::SubWindowView);
    mdiArea->setTabsClosable(false);
    mdiArea->setTabsMovable(false);
    mdiArea->setFrameShape(QFrame::NoFrame);
    // Force light background (Qt's default gradient can ignore QSS)
    mdiArea->setBackground(QBrush(QColor("#FAFBFC")));
    mainLayout->addWidget(mdiArea, /*stretch*/ 1);

    // Right: Timer panel container
    QWidget* rightPanelContainer = new QWidget(centralWidget);
    rightPanelContainer->setObjectName("background1");
    rightPanelContainer->setFixedWidth(240);

    QVBoxLayout* rightLayout = new QVBoxLayout(rightPanelContainer);
    rightLayout->setContentsMargins(0, 0, 0, 0);
    rightLayout->setSpacing(0);

    timerWidget = new TimerWidget(rightPanelContainer);
    timerWidget->setObjectName("background2");
    rightLayout->addWidget(timerWidget);
    rightLayout->addStretch();

    mainLayout->addWidget(rightPanelContainer);

    setCentralWidget(centralWidget);
    setWindowTitle("Smart Study");
    resize(1600, 900);
}

void MainWindow::createMockTextWindow(const QString& topic,
                                      const QString& note)
{
    // Editor widget
    QTextEdit* textEdit = new QTextEdit;
    textEdit->setObjectName("background1");
    textEdit->setFrameStyle(QFrame::NoFrame);
    textEdit->setAcceptRichText(true);
    textEdit->setPlainText(
        QString("%1 / %2\n\n").arg(topic, note) +
        "This is your note content. You can:\n"
        "- Edit freely\n"
        "- Resize window by dragging edges\n"
        "- Drag window by title bar (MDI area)\n"
        "- Auto-saves to local storage (future)\n\n"
        "Mock content for demonstration:\n"
        "════════════════════════════════\n\n"
        "Key Concepts:\n"
        "• Important theoretical points\n"
        "• Formulas and equations\n"
        "• Summary bullet points\n\n"
        "References:\n"
        "• Textbook chapter 5\n"
        "• Lecture notes from Oct 15\n"
        "• Online resources: example.com"
    );

    // Custom subwindow with no OS-like frame buttons
    QMdiSubWindow* subWindow = new QMdiSubWindow;
    subWindow->setWidget(textEdit);
    subWindow->setAttribute(Qt::WA_DeleteOnClose);
    subWindow->setWindowTitle(QString("%1 - %2").arg(topic, note));
    subWindow->setWindowFlags(Qt::FramelessWindowHint | Qt::SubWindow);

    mdiArea->addSubWindow(subWindow);

    subWindow->resize(600, 500);
    subWindow->show();

    // Simple cascading layout
    static int windowOffset = 0;
    const int offset = 40 * (windowOffset % 5);
    subWindow->move(offset, offset);
    ++windowOffset;
}

void MainWindow::onNoteSelected(const QString& topic, const QString& note) {
    qDebug() << "Opening note:" << topic << "/" << note;
    createMockTextWindow(topic, note);
}

void MainWindow::onTimerToggle() {
    bool isRunning = !timerWidget->isRunning();
    timerWidget->setRunning(isRunning);

    if (isRunning) {
        qDebug() << "Timer started";
    } else {
        qDebug() << "Timer paused";
    }
}

void MainWindow::onFlashCardsClicked() {
    // For now, clear editors to simulate mode change
    qDebug() << "Flashcards mode activated";
    mdiArea->closeAllSubWindows();
}