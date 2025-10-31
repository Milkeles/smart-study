#ifndef GUIUTILS_H
#define GUIUTILS_H

#include <QFile>
#include <QGraphicsDropShadowEffect>

namespace GuiUtils {
QGraphicsDropShadowEffect* makeShadow(int blur, QPointF offset, QColor color);

}

#endif