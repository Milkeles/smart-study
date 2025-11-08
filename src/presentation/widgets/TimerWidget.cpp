#include "presentation/widgets/TimerWidget.h"

#include <QTimer>
#include <QPainter>
#include <QPainterPath>
#include <QFont>
#include <QLabel>
#include <QTime>

TimerWidget::TimerWidget(QWidget* parent)
    : QWidget(parent),
      m_running(false),
      m_progress(0.0f)
{
    setAttribute(Qt::WA_StyledBackground, true);
    setupUI();

    // Demo progress timer
    QTimer* demoTimer = new QTimer(this);
    connect(demoTimer, &QTimer::timeout, [this]() {
        if (m_running) {
            m_progress += 0.01f;
            if (m_progress >= 1.0f)
                m_progress = 0.0f;
            update();
        }
    });
    demoTimer->start(100);
}

void TimerWidget::setupUI() {
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->setContentsMargins(16, 32, 16, 32);
    layout->setSpacing(24);

    QLabel* title = new QLabel("Pomodoro", this);
    title->setObjectName("h3");
    title->setAlignment(Qt::AlignCenter);
    layout->addWidget(title);

    QWidget* timerDisplay = new QWidget(this);
    timerDisplay->setFixedSize(200, 200);
    timerDisplay->setObjectName("timerDisplay");
    layout->addWidget(timerDisplay, 0, Qt::AlignCenter);

    playButton = new QPushButton("Start Session", this);
    playButton->setObjectName("PrimaryButton");
    playButton->hide();

    settingsButton = new QPushButton("Timer Settings", this);
    settingsButton->setObjectName("SecondaryButtonOutline");
    settingsButton->hide();

    layout->addWidget(playButton);
    layout->addWidget(settingsButton);
    layout->addStretch();

    connect(playButton,   &QPushButton::clicked, this, &TimerWidget::playClicked);
    connect(settingsButton,&QPushButton::clicked, this, &TimerWidget::settingsClicked);
}

void TimerWidget::setRunning(bool running) {
    m_running = running;
    playButton->setVisible(!running);
    settingsButton->setVisible(!running);
    update();
}

void TimerWidget::paintEvent(QPaintEvent* event) {
    QWidget::paintEvent(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    if (m_running) {
        drawCircularProgress(painter);
    } else {
        drawPlayPauseState(painter);
    }
}

void TimerWidget::drawCircularProgress(QPainter& painter) {
    QWidget* timerDisplay = findChild<QWidget*>("timerDisplay");
    if (!timerDisplay) return;

    QRect rect = timerDisplay->geometry();
    int cx = rect.center().x();
    int cy = rect.center().y();
    int r  = 80;

    // Background ring
    painter.setPen(QPen(QColor("#F1F3F5"), 12, Qt::SolidLine, Qt::RoundCap));
    painter.drawEllipse(cx - r, cy - r, r * 2, r * 2);

    // Progress arc
    QRectF arcRect(cx - r, cy - r, r * 2, r * 2);
    int startAngle = 90 * 16;
    int spanAngle  = -static_cast<int>(m_progress * 360 * 16);

    painter.setPen(QPen(QColor("#C0B7FF"), 12, Qt::SolidLine, Qt::RoundCap));
    painter.drawArc(arcRect, startAngle, spanAngle);

    int totalSeconds = static_cast<int>(25 * 60 * (1.0 - m_progress));
    QTime time(0, totalSeconds / 60, totalSeconds % 60);
    QString timeText = time.toString("mm:ss");

    QFont font = painter.font();
    font.setPointSize(28);
    font.setWeight(QFont::Bold);
    painter.setFont(font);
    painter.setPen(QColor("#212529"));
    painter.drawText(arcRect, Qt::AlignCenter, timeText);
}

void TimerWidget::drawPlayPauseState(QPainter& painter) {
    QWidget* timerDisplay = findChild<QWidget*>("timerDisplay");
    if (!timerDisplay) return;

    QRect rect = timerDisplay->geometry();
    int cx = rect.center().x();
    int cy = rect.center().y();
    int r  = 80;

    // Large play triangle
    QPainterPath path;
    path.moveTo(cx - 40, cy - 50);
    path.lineTo(cx - 40, cy + 50);
    path.lineTo(cx + 50, cy);
    path.closeSubpath();
    painter.fillPath(path, QColor("#C0B7FF"));

    // "Click to start" text
    QFont font = painter.font();
    font.setPointSize(14);
    painter.setFont(font);
    painter.setPen(QColor("#434A4F"));
    painter.drawText(QRect(cx - r, cy + r + 20, r * 2, 30),
                     Qt::AlignCenter,
                     "Click to start");
}