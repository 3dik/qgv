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
#include <QGVEdge.h>
#include <QGVCore.h>
#include <QPainter>

#include <ogdf/labeling/ELabelInterface.h>

const auto labelType = ogdf::LabelType::Name;

QGVEdge::QGVEdge(QGraphicsScene *p, ogdf::edge e, qgv::all_attributes a) :
    GraphElement(p, e, a)
{
    setFlag(QGraphicsItem::ItemIsSelectable, true);
}

QRectF QGVEdge::boundingRect() const
{
    return _path.boundingRect() | _head_arrow.boundingRect() | _tail_arrow.boundingRect() | _label_rect;
}

QPainterPath QGVEdge::shape() const
{
    QPainterPathStroker ps;
    ps.setCapStyle(_pen.capStyle());
    ps.setWidth(_pen.widthF() + 10);
    ps.setJoinStyle(_pen.joinStyle());
    ps.setMiterLimit(_pen.miterLimit());
    return ps.createStroke(_path);
}

void QGVEdge::preprocess()
{
    ogdf::EdgeLabel<double> &data = _attributes.edgeLabels->getLabel(_element);
    data.addType(labelType);
    QSizeF size = QGVCore::sizeOfString(label());
    data.setWidth(labelType, size.width());
    data.setHeight(labelType, size.height());
    _attributes.edgeLabels->setLabel(_element, data);
}

void QGVEdge::paint(QPainter * painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->save();

    if(isSelected())
    {
        QPen tpen(_pen);
        tpen.setColor(_pen.color().darker(120));
        tpen.setStyle(Qt::DotLine);
        painter->setPen(tpen);
    }
    else
        painter->setPen(_pen);


    painter->drawPath(_path);

    painter->drawText(_label_rect, Qt::AlignCenter, label());

    painter->setBrush(QBrush(_pen.color(), Qt::SolidPattern));
    painter->drawPolygon(_head_arrow);
    painter->drawPolygon(_tail_arrow);
    painter->restore();
}

void QGVEdge::updateLayout()
{
    prepareGeometryChange();

    //We only render straight lines because we haven't figured out yet how to
    //do this with OGDF and without any intersections. And because it's easier.
    const ogdf::DPolyline &bends = _attributes.clusterGraph->bends(_element);
    _path = QGVCore::toPath(&bends);

    //Edge arrows
    using ogdf::EdgeArrow;
    EdgeArrow type = _attributes.clusterGraph->arrowType(_element);
    float arrowSize = 10;
    _tail_arrow.clear();
    _head_arrow.clear();
    if(type == EdgeArrow::First || type == EdgeArrow::Both)
    {
        _tail_arrow = toArrow(lineToEndpoint(bends, true, arrowSize));
    }
    if(type == EdgeArrow::Last || type == EdgeArrow::Both)
    {
        _head_arrow = toArrow(lineToEndpoint(bends, false, arrowSize));
    }

    _pen.setWidth(1);

    ogdf::EdgeLabel<double> data = _attributes.edgeLabels->getLabel(_element);
    //not existing labels provide random junk rectangle data
    if (data.usedLabel()) {
        QSizeF size(data.getWidth(labelType), data.getHeight(labelType));
        QPointF pos(data.getX(labelType), data.getY(labelType));
        _label_rect.setSize(size);
        _label_rect.moveCenter(pos);
    }
}

QPolygonF QGVEdge::toArrow(const QLineF &line) const
{
    QLineF n = line.normalVector();
    QPointF o(n.dx() / 3.0, n.dy() / 3.0);

    //Only support normal arrow type
    QPolygonF polygon;
    polygon.append(line.p1() + o);
    polygon.append(line.p2());
    polygon.append(line.p1() - o);

    return polygon;
}

QLineF QGVEdge::lineToEndpoint(const ogdf::DPolyline &lines,
                               bool startPoint, double len)
{
    ogdf::DPoint from, to;
    from = *lines.get(lines.size() - 2);
    to = lines.back();
    if (startPoint)
    {
        from = *lines.get(1);
        to = lines.front();
    }

    //resize with setLength moving p1 instead of p2
    QLineF inverted = QLineF(QGVCore::toPoint(to), QGVCore::toPoint(from));
    inverted.setLength(len);
    return QLineF( inverted.p2(), inverted.p1());
}
