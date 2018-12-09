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
#ifndef QGVNODE_H
#define QGVNODE_H

#include "qgv.h"
#include "QGVElement.h"

#include <QPen>
#include <QFont>

/**
 * @brief Node item
 *
 */
class QGVNode : public GraphElement<ogdf::node, 2>
{
public:
    QGVNode(QGraphicsScene *, ogdf::node, qgv::all_attributes);
    QRectF boundingRect() const;
    void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = 0);
    void preprocess();
    void updateLayout();

private:
    QPen _pen;
    QBrush _brush;
    QSizeF _size;
    QFont _font;
};

#endif // QGVNODE_H
