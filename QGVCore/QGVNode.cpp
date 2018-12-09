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
#include <QGVNode.h>
#include <QGVCore.h>

#include <QPainter>

QGVNode::QGVNode(QGraphicsScene *p, ogdf::node n, qgv::all_attributes a) :
    GraphElement(p, n, a)
{
    setFlag(QGraphicsItem::ItemIsSelectable, true);
}

void QGVNode::preprocess()
{
    //We don't manage node label positioning with OGDF because we don't know
    //how to render the string, the shape etc. in the way OGDF thinks it should
    //be rendered. So until OGDF provides getters for these data, we do it by
    //ourself.
    QSizeF size = QGVCore::sizeOfString(label(), _font) * 1.2;
    size = size.expandedTo(QSizeF( 30, 30));
    _attributes.clusterGraph->width(_element) = size.width();
    _attributes.clusterGraph->height(_element) = size.height();
}

QRectF QGVNode::boundingRect() const
{
    return QRectF(QPointF(), _size);
}

void QGVNode::paint(QPainter * painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->save();

    painter->setPen(_pen);
    painter->setFont(_font);

    if(isSelected())
    {
        QBrush tbrush(_brush);
        tbrush.setColor(tbrush.color().darker(120));
        painter->setBrush(tbrush);
    }
    else
        painter->setBrush(_brush);

    painter->drawRect(boundingRect());
    painter->drawText(boundingRect(), Qt::AlignCenter, GraphElement::label());

    painter->restore();
}

void QGVNode::updateLayout()
{
    prepareGeometryChange();
    QRectF rect = QGVCore::elementRect(_attributes.clusterGraph, _element);
    rect.moveCenter(rect.topLeft()); //ogdf node position is the node's center

    setPos(rect.topLeft());
    _size = rect.size();

    //Node on top
    setZValue(1);

    _pen.setWidth(1);
}
