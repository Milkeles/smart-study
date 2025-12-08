/**
 * @file MainWindow.cpp
 * @brief Implementation of the MainWindow.h class.
 *
 * @author Hristo T. Hristov (milkeles)
 * @date Created: 30/10/2025 (dd/mm/yyyy)
 * @date Updated: 02/12/2025 (dd/mm/yyyy)
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
#include <QTextBrowser>

#include "utils/GuiUtils.h"

const QString STUDY_DIR = QDir::currentPath() + "/src/study_files/";

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    centralWidget = new QWidget(this);
    centralWidget->setObjectName("background1");
    setCentralWidget(centralWidget);

    QHBoxLayout *mainLayout = new QHBoxLayout(centralWidget);
    mainLayout->setContentsMargins(15, 15, 15, 15);
    mainLayout->setSpacing(20);

    // ===== LEFT PANEL =====
    QWidget *leftPanel = new QWidget(centralWidget);
    leftPanel->setObjectName("leftPanel");
    leftPanel->setFixedWidth(250);

    QVBoxLayout *leftLayout = new QVBoxLayout(leftPanel);
    leftLayout->setSpacing(10);

    // Buttons
    importButton = new QPushButton("Import");
    flashcardsButton = new QPushButton("Flash Cards");
    settingsButton = new QPushButton("Settings");
    saveButton = new QPushButton("Save");

    importButton->setObjectName("PrimaryButton");
    flashcardsButton->setObjectName("PrimaryButton");
    settingsButton->setObjectName("PrimaryButton");
    saveButton->setObjectName("PrimaryButton");

    leftLayout->addWidget(importButton);
    leftLayout->addWidget(flashcardsButton);
    leftLayout->addWidget(settingsButton);
    leftLayout->addWidget(saveButton);

    // Files header + "+"
    QWidget *filesHeader = new QWidget(leftPanel);
    QHBoxLayout *filesLayout = new QHBoxLayout(filesHeader);
    filesLayout->setContentsMargins(0, 0, 0, 0);
    filesLayout->setSpacing(5);

    QLabel *filesLabel = new QLabel("Files");
    filesLabel->setStyleSheet("font-weight: bold; font-size: 16px;");

    newFileButton = new QPushButton("+");
    newFileButton->setObjectName("NewFileButton");
    newFileButton->setFixedSize(25, 25);

    filesLayout->addWidget(filesLabel, 1);
    filesLayout->addWidget(newFileButton, 0);

    leftLayout->addWidget(filesHeader);

    // Files tree
    topicsTree = new QTreeWidget();
    topicsTree->setHeaderHidden(true);
    topicsTree->setObjectName("background1");

    loadTopics();
    leftLayout->addWidget(topicsTree, 1);

    // ===== RIGHT PANEL =====
    QWidget *rightPanel = new QWidget(centralWidget);
    QVBoxLayout *rightLayout = new QVBoxLayout(rightPanel);

    QLabel *title = new QLabel("Smart Study");
    title->setObjectName("h1");
    title->setAlignment(Qt::AlignCenter);

    rightLayout->addWidget(title);

    // Mode buttons
    QHBoxLayout *modeButtonsLayout = new QHBoxLayout();
    editModeButton = new QPushButton("Edit");
    previewModeButton = new QPushButton("Preview");

    editModeButton->setObjectName("PrimaryButton");
    previewModeButton->setObjectName("PrimaryButton");

    modeButtonsLayout->addWidget(editModeButton);
    modeButtonsLayout->addWidget(previewModeButton);
    modeButtonsLayout->addStretch();

    rightLayout->addLayout(modeButtonsLayout);

    // Markdown editor (edit mode)
    markdownEditor = new QTextEdit();
    markdownEditor->setObjectName("mdEditor");
    markdownEditor->setPlaceholderText("Write your notes in Markdown…");

    // Markdown preview (preview mode)
    markdownPreview = new QTextBrowser();
    markdownPreview->setObjectName("mdPreview");
    markdownPreview->hide(); // стартово в edit mode

    rightLayout->addWidget(markdownEditor, 1);
    rightLayout->addWidget(markdownPreview, 1);

    // Add panels
    mainLayout->addWidget(leftPanel);
    mainLayout->addWidget(rightPanel, 1);

    // Connections
    connect(topicsTree, &QTreeWidget::itemClicked, this, &MainWindow::onTopicSelected);
    connect(importButton, &QPushButton::clicked, this, &MainWindow::loadMarkdown);
    connect(saveButton, &QPushButton::clicked, this, &MainWindow::saveMarkdown);
    connect(newFileButton, &QPushButton::clicked, this, &MainWindow::createNewFile);
    connect(editModeButton, &QPushButton::clicked, this, &MainWindow::switchToEditMode);
    connect(previewModeButton, &QPushButton::clicked, this, &MainWindow::switchToPreviewMode);

    resize(1300, 800);
}

QString MainWindow::renderMarkdown(const QString &md) {
    QTextDocument doc;
    doc.setMarkdown(md);
    return doc.toHtml();
}

// ===== Methods =====

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
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        markdownEditor->setPlainText(QString::fromUtf8(file.readAll()));
    }
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
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        file.write(markdownEditor->toPlainText().toUtf8());
        file.close();
    }

    loadTopics();
}

void MainWindow::onTopicSelected(QTreeWidgetItem *item) {
    QString topicName = item->text(0);
    currentFilePath = STUDY_DIR + topicName + ".md";

    QFile file(currentFilePath);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        markdownEditor->setPlainText(QString::fromUtf8(file.readAll()));
    }

    switchToEditMode();
}

void MainWindow::loadTopics() {
    topicsTree->clear();

    QDir dir(STUDY_DIR);
    if (!dir.exists()) dir.mkpath(".");

    QStringList mdFiles = dir.entryList({"*.md"}, QDir::Files);
    for (QString name : mdFiles)
        topicsTree->addTopLevelItem(new QTreeWidgetItem(
            { name.chopped(3) }
        ));
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
    if (!file.open(QIODevice::WriteOnly)) {
        qWarning() << "Cannot open file for writing";
    }

    file.close();

    markdownEditor->clear();
    loadTopics();
}

void MainWindow::switchToEditMode() {
    if (!isPreviewMode) return;

    markdownPreview->hide();
    markdownEditor->show();
    markdownEditor->setReadOnly(false);

    // Restore markdown (not HTML)
    QFile file(currentFilePath);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        markdownEditor->setPlainText(QString::fromUtf8(file.readAll()));
    }

    isPreviewMode = false;
}

void MainWindow::switchToPreviewMode() {
    if (isPreviewMode) return;

    QString html = renderMarkdown(markdownEditor->toPlainText());
    markdownPreview->setHtml(html);

    markdownEditor->hide();
    markdownPreview->show();

    isPreviewMode = true;
}
