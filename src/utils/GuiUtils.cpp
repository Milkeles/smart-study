/**
 * @file GuiUtils.cpp
 * @brief Implements GUI Utilities, declared in GuiUtils.h
 *
 * @author Hristo T. Hristov (milkeles)
 * @date Created: 31/10/2025 (dd/mm/yyyy)
 * @date Updated: 31/10/2025 (dd/mm/yyyy)
 */
#include "GuiUtils.h"

QGraphicsDropShadowEffect* GuiUtils::makeShadow(int blur, QPointF offset, QColor color) {
    auto* effect = new QGraphicsDropShadowEffect();
    effect->setBlurRadius(blur);
    effect->setOffset(offset);
    effect->setColor(color);
    return effect;
}
