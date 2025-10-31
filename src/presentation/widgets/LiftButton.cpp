#include "LiftButton.h"
#include <QEvent>
#include <QEasingCurve>

LiftButton::LiftButton(const QString& text, QWidget* parent)
    : QWidget(parent)
{
    auto* layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0); // prevents clipping on hover
    layout->setSpacing(0);

    m_button = new QPushButton(text);
    m_button->setObjectName("PrimaryButton");
    layout->addWidget(m_button);

    // Forward size policy to parent (important!)
    setSizePolicy(m_button->sizePolicy());

    m_anim = new QPropertyAnimation(m_button, "pos", this);
    m_anim->setDuration(100);
    m_anim->setEasingCurve(QEasingCurve::OutQuad);

    m_button->setAttribute(Qt::WA_Hover, true);
    m_button->installEventFilter(this);
}

bool LiftButton::eventFilter(QObject* watched, QEvent* event)
{
    if (watched == m_button) {
        if (event->type() == QEvent::Enter) {
            m_anim->stop();
            m_anim->setEndValue(m_button->pos() - QPoint(0, 2));
            m_anim->start();
        } else if (event->type() == QEvent::Leave) {
            m_anim->stop();
            m_anim->setEndValue(m_button->pos() + QPoint(0, 2));
            m_anim->start();
        }
    }
    return QWidget::eventFilter(watched, event);
}

QSize LiftButton::sizeHint() const {
    return m_button->sizeHint();
}

QSize LiftButton::minimumSizeHint() const {
    return m_button->minimumSizeHint();
}
