#include "presentation/widgets/FlashCardWidget.h"
#include "presentation/widgets/FlashCard.h"

FlashCardWidget::FlashCardWidget(const QVector<FlashCard> &cards,
                                 QWidget *parent)
    : QWidget(parent), cards(cards) {
  label = new QLabel(this);
  label->setAlignment(Qt::AlignCenter);
  label->setWordWrap(true);
  label->setStyleSheet("font-size: 22px; padding: 16px;");

  flipBtn = new QPushButton("Flip");
  flipBtn->setObjectName("PrimaryButton");
  flipBtn->setFixedHeight(40);

  prevBtn = new QPushButton("Previous");
  nextBtn = new QPushButton("Next");
  nextBtn->setObjectName("SecondaryButton");
  prevBtn->setObjectName("SecondaryButton");
  prevBtn->setFixedHeight(40);
  nextBtn->setFixedHeight(40);

  QHBoxLayout *navLayout = new QHBoxLayout;
  navLayout->addWidget(prevBtn);
  navLayout->addWidget(nextBtn);

  QVBoxLayout *mainLayout = new QVBoxLayout(this);
  mainLayout->addWidget(label);
  mainLayout->addWidget(flipBtn);
  mainLayout->addLayout(navLayout);

  connect(flipBtn, &QPushButton::clicked, this, &FlashCardWidget::flipCard);
  connect(nextBtn, &QPushButton::clicked, this, &FlashCardWidget::showNextCard);
  connect(prevBtn, &QPushButton::clicked, this,
          &FlashCardWidget::showPreviousCard);

  updateCardDisplay();
}

void FlashCardWidget::flipCard() {
  showingFront = !showingFront;
  updateCardDisplay();
}

void FlashCardWidget::showNextCard() {
  if (currentIndex + 1 < cards.size()) {
    currentIndex++;
    showingFront = true;
    updateCardDisplay();
  }
}

void FlashCardWidget::showPreviousCard() {
  if (currentIndex > 0) {
    currentIndex--;
    showingFront = true;
    updateCardDisplay();
  }
}

void FlashCardWidget::updateCardDisplay() {
  if (cards.isEmpty()) {
    label->setText("No flashcards available.");
    flipBtn->setEnabled(false);
    nextBtn->setEnabled(false);
    prevBtn->setEnabled(false);
    return;
  }

  const FlashCard &card = cards[currentIndex];
  label->setText(showingFront ? card.question : card.answer);

  prevBtn->setEnabled(currentIndex > 0);
  nextBtn->setEnabled(currentIndex + 1 < cards.size());
  flipBtn->setEnabled(true);
}
