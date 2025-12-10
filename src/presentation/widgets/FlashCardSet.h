#pragma once
#include "FlashCard.h"
#include <QString>
#include <QVector>

struct FlashCardSet {
  QString title;
  QVector<FlashCard> cards;
};
