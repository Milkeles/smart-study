#include "presentation/widgets/FlashCardEditorWidget.h"
#include <QInputDialog>

FlashCardEditorWidget::FlashCardEditorWidget(FlashCardManager *manager,
                                             QWidget *parent)
    : QWidget(parent), manager(manager) {
  QVBoxLayout *layout = new QVBoxLayout(this);

  // QUESTION
  questionLabel = new QLabel("Question:");
  questionLabel->setObjectName("small-secondary-text");
  layout->addWidget(questionLabel);

  questionEdit = new QLineEdit();
  questionEdit->setObjectName("background2");
  layout->addWidget(questionEdit);

  // ANSWER
  answerLabel = new QLabel("Answer:");
  answerLabel->setObjectName("small-secondary-text");
  layout->addWidget(answerLabel);

  answerEdit = new QTextEdit();
  answerEdit->setObjectName("background2");
  layout->addWidget(answerEdit);

  // SET SELECTOR
  QLabel *setLabel = new QLabel("Flashcard Set:");
  setLabel->setObjectName("small-secondary-text");
  layout->addWidget(setLabel);

  setSelector = new QComboBox();
  setSelector->setObjectName("setSelector");
  layout->addWidget(setSelector);

  loadSets();

  // SAVE BUTTON
  saveBtn = new QPushButton("Save Flash Card");
  saveBtn->setFixedHeight(40);
  saveBtn->setObjectName("StartButton");
  layout->addWidget(saveBtn);

  connect(saveBtn, &QPushButton::clicked, this, &FlashCardEditorWidget::onSave);

  // START BUTTON
  startBtn = new QPushButton("Start Flashcards");
  startBtn->setFixedHeight(40);
  layout->addWidget(startBtn);
  layout->setSpacing(12);
  connect(startBtn, &QPushButton::clicked, this,
          &FlashCardEditorWidget::onStart);

  // NEXT & PREVIOUS BUTTONS
  QHBoxLayout *navLayout = new QHBoxLayout();
  prevBtn = new QPushButton("Previous");
  nextBtn = new QPushButton("Next");

  prevBtn->setObjectName("SecondaryButton");
  nextBtn->setObjectName("SecondaryButton");

  navLayout->addWidget(prevBtn);
  navLayout->addWidget(nextBtn);
  layout->addLayout(navLayout);

  connect(nextBtn, &QPushButton::clicked, this, [this]() {
    if (cards.isEmpty())
      return;
    if (currentIndex < cards.size() - 1) {
      currentIndex++;
      questionEdit->setText(cards[currentIndex].question);
      answerEdit->setText(cards[currentIndex].answer);
    }
  });

  connect(prevBtn, &QPushButton::clicked, this, [this]() {
    if (cards.isEmpty())
      return;
    if (currentIndex > 0) {
      currentIndex--;
      questionEdit->setText(cards[currentIndex].question);
      answerEdit->setText(cards[currentIndex].answer);
    }
  });

  // Зареждане на първия сет ако има карти
  connect(setSelector, &QComboBox::currentTextChanged, this,
          [this](const QString &setName) {
            cards = this->manager->getCards(setName);
            currentIndex = 0;
            if (!cards.isEmpty()) {
              questionEdit->setText(cards[currentIndex].question);
              answerEdit->setText(cards[currentIndex].answer);
            } else {
              questionEdit->clear();
              answerEdit->clear();
            }
          });

  // Инициализация на картите за текущия селектиран сет
  QString initialSet = setSelector->currentText();
  if (initialSet != "Create new set...") {
    cards = manager->getCards(initialSet);
    currentIndex = 0;
    if (!cards.isEmpty()) {
      questionEdit->setText(cards[currentIndex].question);
      answerEdit->setText(cards[currentIndex].answer);
    }
  }
}

void FlashCardEditorWidget::loadSets() {
  setSelector->clear();
  setSelector->addItem("Create new set...");

  for (const auto &set : manager->getAllSets()) {
    setSelector->addItem(set.title);
  }
}

void FlashCardEditorWidget::onSave() {
  QString question = questionEdit->text().trimmed();
  QString answer = answerEdit->toPlainText().trimmed();

  if (question.isEmpty() || answer.isEmpty())
    return;

  QString setName = setSelector->currentText();

  if (setName == "Create new set...") {
    bool ok;
    setName =
        QInputDialog::getText(this, "Create New Flashcard Set",
                              "Enter set name:", QLineEdit::Normal, "", &ok);
    if (!ok || setName.trimmed().isEmpty())
      return;

    manager->createSet(setName);
    loadSets();
    setSelector->setCurrentText(setName);
  }

  manager->addCard(setName, question, answer);

  // Обновяване на локалните карти
  cards = manager->getCards(setName);
  currentIndex = cards.size() - 1;

  emit cardCreated(setName);

  questionEdit->clear();
  answerEdit->clear();
}

void FlashCardEditorWidget::onStart() { emit startFlashcardsRequested(); }
