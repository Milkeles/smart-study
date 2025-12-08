#ifndef TIMER_WIDGET_H
#define TIMER_WIDGET_H

#include <QPushButton>
#include <QWidget>

class TimerWidget : public QWidget {
  Q_OBJECT
public:
  explicit TimerWidget(QWidget *parent = nullptr);

signals:
  void playClicked();
  void settingsClicked();

private:
  QPushButton *playButton;
  QPushButton *settingsButton;
};

#endif // TIMER_WIDGET_H
