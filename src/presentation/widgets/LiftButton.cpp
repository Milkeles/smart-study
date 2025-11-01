// TODO: Clipping issue still persists. Fix tomorrow!

#include "LiftButton.h"
#include <QEvent>
#include <QEasingCurve>

LiftButton::LiftButton(const QString& text, QWidget* parent)
    : QWidget(parent)
{

    setMinimumHeight(44);
    auto* layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 2, 0, 2);
    layout->setSpacing(0);
    
    m_button = new QPushButton(text);
    m_button->setObjectName("PrimaryButton");
    layout->addWidget(m_button);
    
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
        QRect currentGeometry = m_button->geometry();
        
        if (event->type() == QEvent::Enter) {
            m_anim->stop();
            m_anim->setPropertyName("geometry");
            QRect lifted = currentGeometry.adjusted(0, -2, 0, -2);
            m_anim->setEndValue(lifted);
            m_anim->start();
        } else if (event->type() == QEvent::Leave) {
            m_anim->stop();
            m_anim->setPropertyName("geometry");
            QRect normal = currentGeometry.adjusted(0, 2, 0, 2);
            m_anim->setEndValue(normal);
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
