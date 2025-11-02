/**
 * @file LiftButton.h
 * @author Hristo T. Hristov (milkeles)
 * @brief Custom widget for QPushButton that lifts 
 * @version 0.1
 * @date 2025-11-02
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#ifndef LIFTBUTTON_H
#define LIFTBUTTON_H

#include <QPushButton>
#include <QPropertyAnimation>
#include <QEnterEvent>

class LiftButton : public QPushButton {
    Q_OBJECT
public:
    LiftButton(const QString& text, QWidget* parent = nullptr)
        : QPushButton(text, parent)
    {
        setMouseTracking(true);
    }

protected:
    void enterEvent(QEnterEvent* event) override {
        animateLift(-2); // lift up 5px
        QPushButton::enterEvent(event);
    }

    void leaveEvent(QEvent* event) override {
        animateLift(2); // back to original position
        QPushButton::leaveEvent(event);
    }

private:
    void animateLift(int yOffset) {
        static const int duration = 120; // ms
        QRect start = geometry();
        QRect end = start;
        end.moveTop(parentWidget()->mapFromGlobal(mapToGlobal(QPoint(0, 0))).y() + yOffset);

        auto* anim = new QPropertyAnimation(this, "geometry");
        anim->setDuration(duration);
        anim->setStartValue(start);
        anim->setEndValue(end);
        anim->setEasingCurve(QEasingCurve::OutQuad);
        anim->start(QAbstractAnimation::DeleteWhenStopped);
    }
};

#endif