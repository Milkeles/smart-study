/**
 * @file TopicsPanel.h
 * @brief Topics navigation panel with expandable topics and notes
 *
 * @author Hristo T. Hristov (milkeles)
 * @date Created: 02/11/2025
 * @date Updated: 02/11/2025
 */

#ifndef TOPICS_PANEL_H
#define TOPICS_PANEL_H

#include <QFrame>
#include <QLabel>
#include <QMap>
#include <QPushButton>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QWidget>

class TopicsPanel : public QWidget {
  Q_OBJECT

public:
  explicit TopicsPanel(QWidget *parent = nullptr);

signals:
  void topicSelected(const QString &topicName);
  void noteSelected(const QString &topicName, const QString &noteName);
  void addTopicClicked();

private:
  void setupUI();
  void createMockData();
  void addTopic(const QString &name, const QStringList &notes,
                bool expanded = false);
  void toggleTopic(const QString &topicName);

  QVBoxLayout *mainLayout;
  QLabel *titleLabel;
  QPushButton *addButton;
  QScrollArea *scrollArea;
  QWidget *scrollContent;
  QVBoxLayout *scrollLayout;

  QMap<QString, QPushButton *> topicButtons;
  QMap<QString, QWidget *> topicNoteContainers;
  QMap<QString, QStringList> topicNotes;
  QMap<QString, bool> topicExpanded;

  QString selectedTopic;
  QString selectedNote;
};

#endif // TOPICS_PANEL_H
