#include "GuiUtils.h"

QGraphicsDropShadowEffect* GuiUtils::makeShadow(int blur = 20, QPointF offset = QPointF(0, 4), QColor color = QColor(0,0,0,80)) {
    auto* effect = new QGraphicsDropShadowEffect();
    effect->setBlurRadius(blur);
    effect->setOffset(offset);
    effect->setColor(color);
    return effect;
}
