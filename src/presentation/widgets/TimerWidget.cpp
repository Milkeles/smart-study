#include "TimerWidget.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPainter>
#include "utils/GuiUtils.h"

TimerWidget::TimerWidget(QWidget *parent)
    : QWidget(parent)
{
    setAttribute(Qt::WA_StyledBackground, true);
    setObjectName("timerCard");

    // Vertical Centering
    auto *outer = new QVBoxLayout(this);
    outer->setContentsMargins(0, 0, 0, 0);
    
    // Horizontal rows
    auto *row = new QHBoxLayout();
    row->setContentsMargins(0, 8, 0, 8);
    row->setSpacing(12);
    row->addStretch();

    playButton = new QPushButton(this);
    playButton->setObjectName("PrimaryButton");
    playButton->setIcon(QIcon(":/resources/icons/play.svg"));
    playButton->setIconSize(QSize(64, 64));
    playButton->setFixedSize(40, 40);
    row->addWidget(playButton);

    settingsButton = new QPushButton(this);
    settingsButton->setObjectName("PrimaryButton");
    settingsButton->setIcon(QIcon(":/resources/icons/settings.svg"));
    settingsButton->setIconSize(QSize(64, 64));
    settingsButton->setFixedSize(40, 40);
    
    row->addWidget(settingsButton);
    row->addStretch();

    outer->addLayout(row);
    outer->addStretch(1);

    connect(playButton,  &QPushButton::clicked, this, &TimerWidget::playClicked);
    connect(settingsButton, &QPushButton::clicked, this, &TimerWidget::settingsClicked);
}