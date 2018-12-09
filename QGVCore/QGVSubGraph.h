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
#ifndef QGVSUBGRAPH_H
#define QGVSUBGRAPH_H

#include "qgv.h"
#include "QGVElement.h"
#include <QPen>

/**
 * @brief SubGraph item
 *
 */
class QGVSubGraph : public GraphElement<ogdf::cluster, 4>
{
public:
    QGVSubGraph(QGraphicsScene *, ogdf::cluster, qgv::all_attributes);

    QRectF boundingRect() const;
    void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = 0);
    void updateLayout();
    void preprocess();

private:
    QSizeF _size;
    QPen _pen;
    QBrush _brush;
};

#endif // QGVSUBGRAPH_H
