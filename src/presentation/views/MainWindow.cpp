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

    // TODO: Services layer.
    connect(sidebar, &Sidebar::noteSelected,
            this, &MainWindow::onNoteSelected);
    connect(sidebar, &Sidebar::flashCardsClicked,
            this, &MainWindow::onFlashCardsClicked);
    connect(timerWidget, &TimerWidget::playClicked,
            this, &MainWindow::onTimerToggle);

    // Demo: initial windows
    createMockTextWindow("Quantum Computing", "Grover's search algorithm");
}

void MainWindow::setupUI() {
    centralWidget = new QWidget(this);
    centralWidget->setObjectName("background1");

    mainLayout = new QHBoxLayout(centralWidget);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);

    sidebar = new Sidebar(centralWidget);
    sidebar->setFixedWidth(280);
    sidebar->setObjectName("background2");
    mainLayout->addWidget(sidebar);

    mdiArea = new QMdiArea(centralWidget);
    mdiArea->setObjectName("background1");
    mdiArea->setViewMode(QMdiArea::SubWindowView);
    mdiArea->setTabsClosable(false);
    mdiArea->setTabsMovable(false);
    mdiArea->setFrameShape(QFrame::NoFrame);

    mdiArea->setBackground(QBrush(QColor("#FAFBFC")));
    mainLayout->addWidget(mdiArea, 1);

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
    QTextEdit* textEdit = new QTextEdit;
    textEdit->setObjectName("background1");
    textEdit->setFrameStyle(QFrame::NoFrame);
    textEdit->setAcceptRichText(true);
    textEdit->setPlainText(
        QString("%1 / %2\n\n").arg(topic, note) +
        "Grover’s search algorithm is a quantum search algorithm, used to find elements in unsorted data of unknown size in O(sqrt(N)) time.\n"
        "An example usecase involves having a list of N possible inputs out of which one satisfies a certain condition. \n"
        "Classical computers would check N/2 elements on average, but quantum computation allows doing it much faster. The algorithm has five steps:\n"
        "1. Start with n qubits in |0> state. Apply Hadamard transformation to create uniform superposition that is equally likely for every possible x.\n"
        "2. Apply the oracle operation to flip the phase of the marked state.\n"
        "3. Apply diffusion to increase the probability of the marked state.\n"
        "4. Repeat about sqrt(N) times, each repetition rotates the state vector closer to the element we’re looking for.\n"
        "5. Measure the qubits, they’re likely to give the correct element with very high probability.\n"
    );

    QMdiSubWindow* subWindow = new QMdiSubWindow;
    subWindow->setWidget(textEdit);
    subWindow->setAttribute(Qt::WA_DeleteOnClose);
    subWindow->setWindowTitle(QString("%1 - %2").arg(topic, note));
    subWindow->setWindowFlags(Qt::FramelessWindowHint | Qt::SubWindow);

    mdiArea->addSubWindow(subWindow);

    subWindow->resize(600, 500);
    subWindow->show();

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
    qDebug() << "Flashcards mode activated";
    mdiArea->closeAllSubWindows();
}