#pragma once
#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QVector>
#include "presentation/widgets/FlashCard.h"  

class FlashCardWidget : public QWidget
{
    Q_OBJECT
public:
    explicit FlashCardWidget(const QVector<FlashCard> &cards, QWidget *parent = nullptr);

private slots:
    void flipCard();
    void showNextCard();
    void showPreviousCard();

private:
    QVector<FlashCard> cards;
    int currentIndex = 0;
    bool showingFront = true;

    QLabel *label;
    QPushButton *flipBtn;
    QPushButton *nextBtn;
    QPushButton *prevBtn;

    void updateCardDisplay();
};
