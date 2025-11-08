/**
 * @file Sidebar.h
 * @brief Sidebar navigation component
 * 
 * Contains main navigation buttons and topics panel
 * 
 * @author Hristo T. Hristov (milkeles)
 * @date Created: 02/11/2025
 * @date Updated: 02/11/2025
 */

#ifndef SIDEBAR_H
#define SIDEBAR_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QFrame>
#include "TopicsPanel.h"

class Sidebar : public QWidget {
    Q_OBJECT

public:
    explicit Sidebar(QWidget* parent = nullptr);

signals:
    void importClicked();
    void flashCardsClicked();
    void settingsClicked();
    void topicSelected(const QString& topicName);
    void noteSelected(const QString& topicName, const QString& noteName);

private:
    void setupUI();

    QVBoxLayout* mainLayout;

    QPushButton* importButton;
    QPushButton* flashCardsButton;
    QPushButton* settingsButton;

    TopicsPanel* topicsPanel;
};

#endif // SIDEBAR_H