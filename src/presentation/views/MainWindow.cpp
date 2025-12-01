/**
 * @file MainWindow.cpp
 * @brief Implementation of the MainWindow.h class.
 *
 * @author Hristo T. Hristov (milkeles)
 * @date Created: 30/10/2025 (dd/mm/yyyy)
 * @date Updated: 30/10/2025 (dd/mm/yyyy)
 */

#include "MainWindow.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QFileDialog>
#include <QFile>
#include <QMessageBox>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QInputDialog>
#include <QLineEdit>


#include "utils/GuiUtils.h"

const QString STUDY_DIR = QDir::currentPath() + "/src/study_files/";

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
centralWidget = new QWidget(this);
    centralWidget->setObjectName("background1");
    setCentralWidget(centralWidget);

    QHBoxLayout *mainLayout = new QHBoxLayout(centralWidget);
    mainLayout->setContentsMargins(15, 15, 15, 15);
    mainLayout->setSpacing(20);

    // ===== LEFT PANEL =======================================
    QWidget *leftPanel = new QWidget(centralWidget);
    leftPanel->setObjectName("leftPanel");
    leftPanel->setFixedWidth(250);

    QVBoxLayout *leftLayout = new QVBoxLayout(leftPanel);
    leftLayout->setSpacing(10);

    // ----- Основни бутони -----
    importButton = new QPushButton("Import");
    importButton->setObjectName("PrimaryButton");
    flashcardsButton = new QPushButton("Flash Cards");
    flashcardsButton->setObjectName("PrimaryButton");
    settingsButton = new QPushButton("Settings");
    settingsButton->setObjectName("PrimaryButton");
    saveButton = new QPushButton("Save");
    saveButton->setObjectName("PrimaryButton");

    leftLayout->addWidget(importButton);
    leftLayout->addWidget(flashcardsButton);
    leftLayout->addWidget(settingsButton);
    leftLayout->addWidget(saveButton);

    // ----- Заглавие "Files" с бутон "+" на едно ниво -----
    QWidget *filesHeader = new QWidget(leftPanel);
    QHBoxLayout *filesLayout = new QHBoxLayout(filesHeader);
    filesLayout->setContentsMargins(0, 0, 0, 0);
    filesLayout->setSpacing(5);

    QLabel *filesLabel = new QLabel("Files");
    filesLabel->setStyleSheet("font-weight: bold; font-size: 16px;");
    filesLabel->setAlignment(Qt::AlignVCenter | Qt::AlignLeft);

    newFileButton = new QPushButton("+");
    newFileButton->setObjectName("NewFileButton");
    newFileButton->setFixedSize(25, 25);
    newFileButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    filesLayout->addWidget(filesLabel, 1, Qt::AlignVCenter);
    filesLayout->addWidget(newFileButton, 0, Qt::AlignVCenter);

    leftLayout->addWidget(filesHeader);

    // ---- Topics tree --------------------------
    topicsTree = new QTreeWidget();
    topicsTree->setHeaderHidden(true);
    topicsTree->setObjectName("background1");

    loadTopics(); // зареждаме файловете от директорията
    leftLayout->addWidget(topicsTree, 1);

    // ===== RIGHT PANEL =======================================
    QWidget *rightPanel = new QWidget(centralWidget);
    rightPanel->setObjectName("rightPanel");
    QVBoxLayout *rightLayout = new QVBoxLayout(rightPanel);

    QLabel *title = new QLabel("Smart Study");
    title->setObjectName("h1");
    title->setAlignment(Qt::AlignCenter);
    rightLayout->addWidget(title);

    markdownEditor = new QTextEdit();
    markdownEditor->setObjectName("mdEditor");
    markdownEditor->setPlaceholderText("Write your notes in Markdown…");
    markdownEditor->setObjectName("background1");
    rightLayout->addWidget(markdownEditor, 1);

    // ===== Add to main layout ========================================
    mainLayout->addWidget(leftPanel);
    mainLayout->addWidget(rightPanel, 1);

    // ===== Connections =======================================
    connect(topicsTree, &QTreeWidget::itemClicked, this, &MainWindow::onTopicSelected);
    connect(importButton, &QPushButton::clicked, this, &MainWindow::loadMarkdown);
    connect(saveButton, &QPushButton::clicked, this, &MainWindow::saveMarkdown);
    connect(newFileButton, &QPushButton::clicked, this, &MainWindow::createNewFile);

    resize(1300, 800);
}

// ===== Методи =============================================

void MainWindow::loadMarkdown() {
    QString imported = QFileDialog::getOpenFileName(
        this, "Import Markdown File", "", "Markdown (*.md)"
    );

    if (imported.isEmpty()) return;

    if (currentFilePath.isEmpty()) {
        QMessageBox::warning(this, "Select Topic",
                             "Select a topic before importing a note.");
        return;
    }

    QFile::copy(imported, currentFilePath);

    QFile file(currentFilePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Error", "Cannot open imported file.");
        return;
    }

    markdownEditor->setText(QString::fromUtf8(file.readAll()));
}

void MainWindow::saveMarkdown() {
    if (currentFilePath.isEmpty()) {
        bool ok;
        QString newName = QInputDialog::getText(
            this, "New File", "Enter file name:", QLineEdit::Normal, "", &ok
        );
        if (!ok || newName.isEmpty()) return;
        currentFilePath = STUDY_DIR + newName + ".md";
    }

    QDir().mkpath(QFileInfo(currentFilePath).absolutePath());

    QFile file(currentFilePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::critical(this, "Error", "Cannot save file.");
        return;
    }

    file.write(markdownEditor->toPlainText().toUtf8());
    file.close();

    QMessageBox::information(this, "Saved", "Note saved in study_files!");
    loadTopics();
}

void MainWindow::onTopicSelected(QTreeWidgetItem *item) {
    QString topicName = item->text(0);
    QString filePath = STUDY_DIR + topicName + ".md";

    QFile file(filePath);
    if (file.exists() && file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        markdownEditor->setText(QString::fromUtf8(file.readAll()));
        currentFilePath = filePath;
    } else {
        markdownEditor->clear();
        currentFilePath = filePath;
    }
}

void MainWindow::loadTopics() {
    topicsTree->clear();

    QDir dir(STUDY_DIR);
    if (!dir.exists()) {
        dir.mkpath(".");
    }

    QStringList mdFiles = dir.entryList(QStringList() << "*.md", QDir::Files);
    for (const QString &fileName : mdFiles) {
        QTreeWidgetItem *item = new QTreeWidgetItem({fileName.left(fileName.length() - 3)});
        topicsTree->addTopLevelItem(item);
    }
}

void MainWindow::createNewFile() {
    bool ok;
    QString newName = QInputDialog::getText(
        this, "New File", "Enter file name:", QLineEdit::Normal, "", &ok
    );

    if (!ok || newName.isEmpty()) return;

    currentFilePath = STUDY_DIR + newName + ".md";

    QDir().mkpath(QFileInfo(currentFilePath).absolutePath());
    QFile file(currentFilePath);
    if (file.open(QIODevice::WriteOnly)) {
        file.close();
    }

    markdownEditor->clear();
    loadTopics();
}