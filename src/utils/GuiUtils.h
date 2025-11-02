/**
 * @file GuiUtils.h
 * @brief Namespace of GUI Utilities
 *
 * This namespace includes useful utilities that can be used across multiple UI views.
 * - addShadowEffect - adds dropshadow to Qt elements.
 * - addLiftEffect   - adds lift effect on hover to Qt elements.
 * 
 * Libraries:
 * - QGraphicsDropShadowEffect - necessary for the drop shadow effect.
 * 
 * @author Hristo T. Hristov (milkeles)
 * @date Created: 31/10/2025 (dd/mm/yyyy)
 * @date Updated: 02/11/2025 (dd/mm/yyyy)
 */

#ifndef GUIUTILS_H
#define GUIUTILS_H

#include <QObject>
#include <QWidget>
#include <QGraphicsDropShadowEffect>
#include <QPoint>
#include <QEasingCurve>
#include <functional>
#include <QSet>
#include <QApplication>
#include <QEvent>

class TranslateFilter : public QObject {
    Q_OBJECT
    
    QWidget* target;
    QPoint offset;
    int duration;
    QEasingCurve::Type easing;
    QRect original;

public:
    TranslateFilter(QWidget* w, QPoint offset, int durationMs, QEasingCurve::Type easingType);
    
protected:
    bool eventFilter(QObject* obj, QEvent* event) override;
    
private:
    void animateTo(const QRect& endRect);
};

namespace GuiUtils {
    enum class WidgetState {
        Hover,
        Pressed,
        Default
    };
    
    /**
     * @brief Adds drop shadow effect to widgets or graphics items.
     *
     * @param target    The target element the effect is added to.
     * @param blur      The blur radius of the shadow, in pixels.  
     *                  **Default:** `15`
     * @param offset    The offset of the shadow relative to the source item.  
     *                  **Default:** `QPointF(0, 4)`
     * @param color     The color of the shadow, including its alpha (transparency) component.  
     *                  **Default:** `QColor(0, 0, 0, 80)`
     */
    void addShadowEffect(QWidget* target,
                                int blur = 15,
                                QPointF offset = {0, 4},
                                QColor color = QColor(0, 0, 0, 80));

    /**
     * @brief Adds a translation effect to a widgets or graphic items.
     * 
     * @param target     The target element the effect is added to.
     * @param offset     The amount by which the element is translated in each axis.
     *                   **Default:** `{0, -2}`
     * @param duration   The duration of the animation (ms).
     *                   **Default:** `120`
     * @param easing     The easing style of the animation.
     *                   **Default:** `OutQuad`
     */
    void addTranslateEffect(QWidget* target,
                                   QPoint offset = {0, -2},
                                   int duration = 120,
                                   QEasingCurve::Type easing = QEasingCurve::OutQuad);

    /**
     * @brief Globally installs effect to all widgets of certain type.
     * 
     * @tparam WidgetType 
     * @param effectFunc Function of the installed effect.
     * @param triggerState State in which this effect should be triggered (Default, Hover, or Pressed).
     */
    template<typename WidgetType>
    void installGlobalEffect(std::function<void(QWidget *)> effectFunc,
                                    WidgetState triggerState);
}

template<typename WidgetType>
class GlobalEffectFilter : public QObject {
    GuiUtils::WidgetState triggerState;
    std::function<void(QWidget*)> effectFunc;
    QSet<QWidget*> processed;
public:
    GlobalEffectFilter(GuiUtils::WidgetState state,
                       std::function<void(QWidget*)> func)
        : triggerState(state), effectFunc(std::move(func)) {}
protected:
    bool eventFilter(QObject* obj, QEvent* event) override {
        auto* w = qobject_cast<WidgetType*>(obj);
        if (!w) return QObject::eventFilter(obj, event);

        bool shouldApply = false;

        switch (triggerState) {
            case GuiUtils::WidgetState::Hover:
                shouldApply = (event->type() == QEvent::Enter);
                break;
            case GuiUtils::WidgetState::Pressed:
                shouldApply = (event->type() == QEvent::MouseButtonPress);
                break;
            case GuiUtils::WidgetState::Default:
                shouldApply = (event->type() == QEvent::Show || event->type() == QEvent::Polish);
                break;
        }

        if (shouldApply && !processed.contains(w)) {
            processed.insert(w);
            effectFunc(w);
        }

        return QObject::eventFilter(obj, event);
    }
};

template<typename WidgetType>
void GuiUtils::installGlobalEffect(std::function<void(QWidget*)> effectFunc, WidgetState triggerState) {
    qApp->installEventFilter(new GlobalEffectFilter<WidgetType>(triggerState, std::move(effectFunc)));
}

#endif