/**
 * @file GuiUtils.cpp
 * @brief Implements GUI Utilities, declared in GuiUtils.h
 *
 * @author Hristo T. Hristov (milkeles)
 * @date Created: 31/10/2025 (dd/mm/yyyy)
 * @date Updated: 02/11/2025 (dd/mm/yyyy)
 */

#include "GuiUtils.h"
#include <QPropertyAnimation>
#include <QDebug>

// TranslateFilter implementation
TranslateFilter::TranslateFilter(QWidget* w, QPoint offset, int durationMs, QEasingCurve::Type easingType)
    : QObject(w), target(w), offset(offset), duration(durationMs), easing(easingType) {}

bool TranslateFilter::eventFilter(QObject* obj, QEvent* event) {
    if (obj != target)
        return QObject::eventFilter(obj, event);

    switch (event->type()) {
    case QEvent::Enter:
        if (original.isNull())
            original = target->geometry();
        animateTo(original.translated(offset));
        break;
    case QEvent::Leave:
        animateTo(original);
        break;
    case QEvent::MouseButtonPress:
        animateTo(original.translated(offset / 2));
        break;
    case QEvent::MouseButtonRelease:
        animateTo(original.translated(offset));
        break;
    default:
        break;
    }
    return QObject::eventFilter(obj, event);
}

void TranslateFilter::animateTo(const QRect& endRect) {
    QRect start = target->geometry();
    auto* anim = new QPropertyAnimation(target, "geometry");
    anim->setDuration(duration);
    anim->setStartValue(start);
    anim->setEndValue(endRect);
    anim->setEasingCurve(QEasingCurve(easing));
    anim->start(QAbstractAnimation::DeleteWhenStopped);
}

// Effect implementations
void GuiUtils::addShadowEffect(QWidget* widget, int blur, QPointF offset, QColor color) {
    if (!widget) return;
    auto* effect = new QGraphicsDropShadowEffect();
    effect->setBlurRadius(blur);
    effect->setOffset(offset);
    effect->setColor(color);
    widget->setGraphicsEffect(effect);
}

void GuiUtils::addTranslateEffect(QWidget* widget, QPoint offset, int duration, QEasingCurve::Type easing) {
    if (!widget) return;

    widget->installEventFilter(new TranslateFilter(widget, offset, duration, easing));
    widget->setMouseTracking(true);
}