#include "presentation/widgets/TopicsPanel.h"
#include <QDebug>
#include <QScrollBar>

TopicsPanel::TopicsPanel(QWidget *parent) : QWidget(parent) {
  setupUI();
  createMockData();
}

void TopicsPanel::setupUI() {
  mainLayout = new QVBoxLayout(this);
  mainLayout->setContentsMargins(16, 0, 16, 16);
  mainLayout->setSpacing(0);

  QFrame *card = new QFrame(this);
  card->setObjectName("topicsCard");
  card->setFrameShape(QFrame::NoFrame);
  card->setAttribute(Qt::WA_StyledBackground, true);

  QVBoxLayout *cardLayout = new QVBoxLayout(card);
  cardLayout->setContentsMargins(16, 16, 16, 16);
  cardLayout->setSpacing(8);

  QHBoxLayout *headerLayout = new QHBoxLayout();
  headerLayout->setContentsMargins(0, 0, 0, 0);
  headerLayout->setSpacing(8);

  titleLabel = new QLabel("Topics", card);
  titleLabel->setObjectName("h3");

  addButton = new QPushButton("+", card);
  addButton->setObjectName("TopicsAddButton");

  int labelH = titleLabel->sizeHint().height();
  int buttonSize = static_cast<int>(labelH * 1.3);

  addButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
  addButton->setFixedSize(buttonSize, buttonSize);

  QFont plusFont = addButton->font();
  plusFont.setPointSizeF(titleLabel->font().pointSizeF() * 0.9);
  plusFont.setBold(true);
  addButton->setFont(plusFont);

  headerLayout->addWidget(titleLabel);
  headerLayout->addStretch();
  headerLayout->addWidget(addButton);
  headerLayout->setAlignment(addButton, Qt::AlignVCenter);

  cardLayout->addLayout(headerLayout);

  scrollArea = new QScrollArea(card);
  scrollArea->setWidgetResizable(true);
  scrollArea->setFrameShape(QFrame::NoFrame);
  scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  scrollArea->viewport()->setAutoFillBackground(false);

  scrollContent = new QWidget(scrollArea);

  scrollContent->setObjectName("background2");
  scrollContent->setAttribute(Qt::WA_StyledBackground, true);

  scrollLayout = new QVBoxLayout(scrollContent);
  scrollLayout->setContentsMargins(0, 8, 0, 8);
  scrollLayout->setSpacing(4);

  scrollLayout->setAlignment(Qt::AlignTop);

  scrollArea->setWidget(scrollContent);

  cardLayout->addWidget(scrollArea, 1);

  mainLayout->addWidget(card);

  connect(addButton, &QPushButton::clicked, this,
          &TopicsPanel::addTopicClicked);
}

void TopicsPanel::createMockData() {
  addTopic("Quantum Computing",
           {"Superposition", "Grover's search algorithm", "Tonsors", "Entanglement"});
  addTopic("C++ Programming",
           {"Pointers", "Templates", "Qt Basics", "Memory Management"});
  addTopic("History", {"World War II", "Cold War", "Modern Era"});
  addTopic("Mathematics", {"Linear Algebra", "Calculus", "Statistics"});
}

void TopicsPanel::addTopic(const QString& name,
                           const QStringList& notes,
                           bool expanded)
{

    QPushButton* topicBtn = new QPushButton(name, scrollContent);
    topicBtn->setObjectName("topicItem");
    topicBtn->setCheckable(true);
    topicBtn->setChecked(expanded);
    topicBtn->setText(expanded ? "▼ " + name : "▶ " + name);

    topicButtons[name]  = topicBtn;
    topicNotes[name]    = notes;
    topicExpanded[name] = expanded;

    connect(topicBtn, &QPushButton::clicked, [this, name]() {
        toggleTopic(name);
        emit topicSelected(name);
    });

    scrollLayout->addWidget(topicBtn);

    QWidget* notesContainer = new QWidget(scrollContent);
    QVBoxLayout* notesLayout = new QVBoxLayout(notesContainer);
    notesLayout->setContentsMargins(24, 0, 0, 0);
    notesLayout->setSpacing(2);

    for (const QString& note : notes) {
        QPushButton* noteBtn = new QPushButton(note, notesContainer);
        noteBtn->setObjectName("noteItem");
        noteBtn->setCheckable(true);

        connect(noteBtn, &QPushButton::clicked, [this, name, note, noteBtn]() {
            // uncheck others for this topic
            QWidget* container = topicNoteContainers[name];
            for (int i = 0; i < container->layout()->count(); ++i) {
                auto* otherBtn = qobject_cast<QPushButton*>(
                    container->layout()->itemAt(i)->widget());
                if (otherBtn && otherBtn != noteBtn)
                    otherBtn->setChecked(false);
            }

            selectedTopic = name;
            selectedNote  = note;
            emit noteSelected(name, note);
        });

        notesLayout->addWidget(noteBtn);
    }

    topicNoteContainers[name] = notesContainer;
    notesContainer->setVisible(expanded);

    scrollLayout->addWidget(notesContainer);
}

void TopicsPanel::toggleTopic(const QString& topicName) {
    bool expanded = !topicExpanded.value(topicName, false);
    topicExpanded[topicName] = expanded;

    QWidget* container = topicNoteContainers.value(topicName, nullptr);
    QPushButton* button = topicButtons.value(topicName, nullptr);
    if (!container || !button)
        return;

    button->setChecked(expanded);
    button->setText(expanded ? "▼ " + topicName : "▶ " + topicName);
    container->setVisible(expanded);
}
