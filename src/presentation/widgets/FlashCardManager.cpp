#include "FlashCardManager.h"

FlashCardManager::FlashCardManager() {}

void FlashCardManager::createSet(const QString &setName) {
  FlashCardSet newSet;
  newSet.title = setName;
  sets.push_back(newSet);
}

void FlashCardManager::addCard(const QString &setName, const QString &question,
                               const QString &answer) {
  for (auto &set : sets) {
    if (set.title == setName) {
      set.cards.push_back({question, answer});
      return;
    }
  }

  // Ако сетът не съществува → създаваме нов
  FlashCardSet newSet;
  newSet.title = setName;
  newSet.cards.push_back({question, answer});
  sets.push_back(newSet);
}

FlashCardSet *FlashCardManager::getSet(const QString &setName) {
  for (auto &set : sets) {
    if (set.title == setName)
      return &set;
  }
  return nullptr;
}

const QVector<FlashCardSet> &FlashCardManager::getAllSets() const {
  return sets;
}

QVector<FlashCard> FlashCardManager::getCards(const QString &setName) const {
  for (const auto &set : sets) { // sets е твоят контейнер с всички FlashCardSet
    if (set.title == setName)
      return set.cards;
  }
  return {};
}