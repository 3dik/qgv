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
#ifndef QGVEDGE_H
#define QGVEDGE_H

#include "qgv.h"
#include "QGVElement.h"
#include <QPen>

class QGVScene;

/**
 * @brief Edge item
 *
 */
class QGVEdge : public GraphElement<ogdf::edge, 3>
{
public:
    QGVEdge(QGraphicsScene *, ogdf::edge, qgv::all_attributes);
    QRectF boundingRect() const;
    void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = 0);
    void preprocess();
    void updateLayout();
    QPainterPath shape() const;

private:
    QPolygonF toArrow(const QLineF &normal) const;
    QLineF lineToEndpoint(const ogdf::DPolyline &lines,
                          bool startPoint, double len);

    QPainterPath _path;
    QPen _pen;
    QPolygonF _head_arrow;
    QPolygonF _tail_arrow;

    QRectF _label_rect;
};

#endif // QGVEDGE_H
