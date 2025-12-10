#pragma once
#include "FlashCardSet.h"
#include <QString>
#include <QVector>

class FlashCardManager {
public:
  FlashCardManager();

  // Създаване на нов сет (тема)
  void createSet(const QString &setName);

  // Добавяне на карта към даден сет
  void addCard(const QString &setName, const QString &question,
               const QString &answer);

  // Връща указател към сет (nullptr ако не съществува)
  FlashCardSet *getSet(const QString &setName);

  // Връща всички сетове (за UI)
  const QVector<FlashCardSet> &getAllSets() const;

  QVector<FlashCard> getCards(const QString &setName) const;

private:
  QVector<FlashCardSet> sets;
};
