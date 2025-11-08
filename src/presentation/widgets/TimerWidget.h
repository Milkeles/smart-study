#ifndef TIMER_WIDGET_H
#define TIMER_WIDGET_H

#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>

class TimerWidget : public QWidget {
  Q_OBJECT

public:
  explicit TimerWidget(QWidget *parent = nullptr);

  void setRunning(bool running);
  bool isRunning() const { return m_running; }

signals:
  void playClicked();
  void settingsClicked();

protected:
  void paintEvent(QPaintEvent *event) override;

private:
  void setupUI();
  void drawCircularProgress(QPainter &painter);
  void drawPlayPauseState(QPainter &painter);

  bool m_running;
  float m_progress;

  QPushButton *playButton;
  QPushButton *settingsButton;
};

#endif // TIMER_WIDGET_H
