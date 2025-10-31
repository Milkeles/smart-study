/**
 * @file GuiUtils.h
 * @brief Namespace of GUI Utilities
 *
 * This namespace includes useful utilities that can be used across multiple UI views.
 * - makeShadow - creates a reusable drop shadow effect for Qt widgets.
 * 
 * Libraries:
 * - QGraphicsDropShadowEffect - necessary for the drop shadow effect.
 * 
 * @author Hristo T. Hristov (milkeles)
 * @date Created: 31/10/2025 (dd/mm/yyyy)
 * @date Updated: 31/10/2025 (dd/mm/yyyy)
 */

#ifndef GUIUTILS_H
#define GUIUTILS_H

#include <QGraphicsDropShadowEffect>

namespace GuiUtils {

    /**
     * @brief Creates a new drop shadow effect for use with widgets or graphics items.
     *
     * Constructs and configures a `QGraphicsDropShadowEffect` using the specified
     * parameters or their default values. This is useful for applying consistent
     * shadow styling across different widgets or views in the application.
     *
     * @param blur The blur radius of the shadow, in pixels.  
     *             **Default:** `20`
     * @param offset The offset of the shadow relative to the source item.  
     *               **Default:** `QPointF(0, 4)`
     * @param color The color of the shadow, including its alpha (transparency) component.  
     *              **Default:** `QColor(0, 0, 0, 80)`
     * 
     * @return A pointer to a new `QGraphicsDropShadowEffect` configured with the
     * given parameters. The caller takes ownership of the returned pointer and
     * must ensure it is deleted or assigned to a Qt parent.
     *
     * @note Typical usage:
     * @code
     * myWidget->setGraphicsEffect(
     *     GuiUtils::makeShadow(20, QPointF(0, 4), QColor(0, 0, 0, 80))
     * );
     * @endcode
     */
    QGraphicsDropShadowEffect* makeShadow(int blur = 20, QPointF offset = QPointF(0, 4), QColor color = QColor(0, 0, 0, 80));
}

#endif