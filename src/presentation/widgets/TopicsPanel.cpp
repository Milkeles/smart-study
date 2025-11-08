#include "presentation/widgets/TopicsPanel.h"
#include <QScrollBar>
#include <QDebug>

TopicsPanel::TopicsPanel(QWidget* parent)
    : QWidget(parent)
{
    setupUI();
    createMockData();
}

void TopicsPanel::setupUI() {
    // This whole widget lives in the sidebar – give some padding from the edges
    mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(16, 0, 16, 16);
    mainLayout->setSpacing(0);

    // Card frame (rounded, light background)
    QFrame* card = new QFrame(this);
    card->setObjectName("topicsCard");
    card->setFrameShape(QFrame::NoFrame);
    card->setAttribute(Qt::WA_StyledBackground, true);

    QVBoxLayout* cardLayout = new QVBoxLayout(card);
    cardLayout->setContentsMargins(16, 16, 16, 16);
    cardLayout->setSpacing(8);

    // === Header inside the card: "Topics" + "+" ===
    QHBoxLayout* headerLayout = new QHBoxLayout();
    headerLayout->setContentsMargins(0, 0, 0, 0);
    headerLayout->setSpacing(8);

    titleLabel = new QLabel("Topics", card);
    titleLabel->setObjectName("h3");

    addButton = new QPushButton("+", card);
    addButton->setObjectName("PrimaryButton");
    addButton->setFixedSize(40, 40);

    headerLayout->addWidget(titleLabel);
    headerLayout->addStretch();
    headerLayout->addWidget(addButton);

    cardLayout->addLayout(headerLayout);

    // === Scroll area (still inside the card) ===
    scrollArea = new QScrollArea(card);
    scrollArea->setWidgetResizable(true);
    scrollArea->setFrameShape(QFrame::NoFrame);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollArea->viewport()->setAutoFillBackground(false);

    scrollContent = new QWidget(scrollArea);
    // IMPORTANT: give the content the light background explicitly
    scrollContent->setObjectName("background2");
    scrollContent->setAttribute(Qt::WA_StyledBackground, true);

    scrollLayout = new QVBoxLayout(scrollContent);
    scrollLayout->setContentsMargins(0, 8, 0, 0);
    scrollLayout->setSpacing(4);
    scrollLayout->addStretch();

    scrollArea->setWidget(scrollContent);

    cardLayout->addWidget(scrollArea, 1);

    mainLayout->addWidget(card);

    connect(addButton, &QPushButton::clicked,
            this, &TopicsPanel::addTopicClicked);
}

void TopicsPanel::createMockData() {
    addTopic("Quantum Physics",  {"Introduction", "Wave Functions", "Entanglement", "Experiments"});
    addTopic("C++ Programming", {"Pointers", "Templates", "Qt Basics", "Memory Management"});
    addTopic("History",         {"World War II", "Cold War", "Modern Era"});
    addTopic("Mathematics",     {"Linear Algebra", "Calculus", "Statistics"});
}

void TopicsPanel::addTopic(const QString& name,
                           const QStringList& notes,
                           bool expanded)
{
    // Topic button
    QPushButton* topicBtn = new QPushButton(name, scrollContent);
    topicBtn->setObjectName("topicItem");
    topicBtn->setCheckable(true);
    topicBtn->setChecked(expanded);
    topicBtn->setText(expanded ? "▼ " + name : "▶ " + name);

    topicButtons[name]   = topicBtn;
    topicNotes[name]     = notes;
    topicExpanded[name]  = expanded;

    connect(topicBtn, &QPushButton::clicked, [this, name, topicBtn]() {
        toggleTopic(name);
        topicBtn->setText(topicBtn->isChecked() ? "▼ " + name : "▶ " + name);
        emit topicSelected(name);
    });

    // Notes container
    QWidget* notesContainer = new QWidget(scrollContent);
    QVBoxLayout* notesLayout = new QVBoxLayout(notesContainer);
    notesLayout->setContentsMargins(24, 0, 0, 0);
    notesLayout->setSpacing(2);

    if (!expanded)
        notesContainer->hide();

    for (const QString& note : notes) {
        QPushButton* noteBtn = new QPushButton(note, notesContainer);
        noteBtn->setObjectName("noteItem");
        noteBtn->setCheckable(true);

        connect(noteBtn, &QPushButton::clicked, [this, name, note, noteBtn]() {
            // Uncheck other notes in this topic
            QWidget* container = topicNoteContainers[name];
            for (int i = 0; i < container->layout()->count(); ++i) {
                auto* otherBtn =
                    qobject_cast<QPushButton*>(container->layout()->itemAt(i)->widget());
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

    // Insert before the stretch at the end
    int idx = scrollLayout->count() - 1;
    scrollLayout->insertWidget(idx, topicBtn);
    scrollLayout->insertWidget(idx + 1, notesContainer);

    if (expanded)
        notesContainer->show();
}

void TopicsPanel::toggleTopic(const QString& topicName) {
    bool expanded = !topicExpanded[topicName];
    topicExpanded[topicName] = expanded;

    QWidget* container = topicNoteContainers[topicName];
    QPushButton* topicBtn = topicButtons[topicName];
    topicBtn->setChecked(expanded);

    // No animations – just show/hide to avoid glitches
    if (expanded) {
        container->show();
    } else {
        container->hide();
    }
}
