#include "presentation/widgets/Sidebar.h"

#include "utils/GuiUtils.h"
#include <QFrame>

Sidebar::Sidebar(QWidget *parent) : QWidget(parent) {
  setObjectName("background2");

  GuiUtils::addShadowEffect(this, 15, {4.0, 0});

  mainLayout = new QVBoxLayout(this);
  mainLayout->setContentsMargins(0, 0, 0, 0);
  mainLayout->setSpacing(32);

  QFrame *navFrame = new QFrame(this);
  navFrame->setObjectName("background2");
  QVBoxLayout *navLayout = new QVBoxLayout(navFrame);
  navLayout->setContentsMargins(16, 32, 16, 0);
  navLayout->setSpacing(16);

  importButton = new QPushButton("Import", navFrame);
  importButton->setObjectName("PrimaryButton");

  flashCardsButton = new QPushButton("Flash Cards", navFrame);
  flashCardsButton->setObjectName("PrimaryButton");

  settingsButton = new QPushButton("Settings", navFrame);
  settingsButton->setObjectName("PrimaryButton");

  navLayout->addWidget(importButton);
  navLayout->addWidget(flashCardsButton);
  navLayout->addWidget(settingsButton);
  navLayout->addStretch();

  topicsPanel = new TopicsPanel(this);

  mainLayout->addWidget(navFrame);
  mainLayout->addWidget(topicsPanel, 1);

  connect(importButton, &QPushButton::clicked, this, &Sidebar::importClicked);
  connect(flashCardsButton, &QPushButton::clicked, this,
          &Sidebar::flashCardsClicked);
  connect(settingsButton, &QPushButton::clicked, this,
          &Sidebar::settingsClicked);

  connect(topicsPanel, &TopicsPanel::topicSelected, this,
          &Sidebar::topicSelected);
  connect(topicsPanel, &TopicsPanel::noteSelected, this,
          &Sidebar::noteSelected);
}
