#pragma once
#include <QString>
#include <QVector>
#include "FlashCard.h"

struct FlashCardSet {
    QString title;
    QVector<FlashCard> cards;
};
