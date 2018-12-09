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
#include "QGVCore.h"

QPointF QGVCore::toPoint(ogdf::DPoint point)
{
    return QPointF(point.m_x, point.m_y);
}

QPainterPath QGVCore::toPath(const ogdf::DPolyline *line)
{
    QPainterPath path;
    ogdf::ListConstIterator<ogdf::DPoint> it = line->begin();
    path.moveTo((*it).m_x, (*it).m_y);
    for (it++; it.valid(); it++)
    {
        path.lineTo((*it).m_x, (*it).m_y);
    }
    return path;
}

QSizeF QGVCore::sizeOfString(QString string, QFont font)
{
    return QFontMetrics(font).boundingRect(string).size();
}
