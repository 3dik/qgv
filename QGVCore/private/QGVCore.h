/***************************************************************
QGVCore
Copyright (c) 2014, Bergont Nicolas, All rights reserved.

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 3.0 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library.
***************************************************************/

#ifndef QGVCORE_H
#define QGVCORE_H

#include <QPolygonF>
#include <QPainterPath>
#include <QColor>
#include <QFontMetrics>

#include <ogdf/cluster/ClusterGraphAttributes.h>

/**
 * @brief OGDF to GraphicsScene conversions
 *
 */
class QGVCore
{
public:
    static QPointF toPoint(ogdf::DPoint point);
    static QPainterPath toPath(const ogdf::DPolyline *line);
    static QSizeF sizeOfString(QString, QFont=QFont());

    template<class T>
    static QRectF elementRect(const ogdf::ClusterGraphAttributes *a, T *e)
    {
        return QRectF(a->x(e), a->y(e), a->width(e), a->height(e));
    }
};

#endif // QGVCORE_H
