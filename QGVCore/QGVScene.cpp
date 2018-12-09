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
#include "QGVScene.h"
// The following include allows the automoc to detect, that it must moc this class
#include "moc_QGVScene.cpp"

#include <QGVNode.h>
#include <QGVEdge.h>
#include <QGVSubGraph.h>

#include <QGVCore.h>

QGVScene::QGVScene(QObject *parent): QGraphicsScene(parent) {}

void QGVScene::loadGraph(qgv::all_attributes attr)
{
    _elements.clear();
    _attributes = attr;

    const ogdf::Graph &graph = attr.clusterGraph->constGraph();
    for (ogdf::node node : graph.nodes)
    {
        add(node);
    }
    for (ogdf::edge edge : graph.edges)
    {
        add(edge);
    }
    const ogdf::ClusterGraph &cGraph = attr.clusterGraph->constClusterGraph();
    for (ogdf::cluster cluster : cGraph.clusters)
    {
        add(cluster);
    }
}

void QGVScene::preprocess()
{
    for (auto &p : _elements)
    {
        p->preprocess();
    }
}

void QGVScene::applyLayout()
{
    for (auto &p : _elements)
    {
        p->updateLayout();
    }

    update();
}

#include <QGraphicsSceneContextMenuEvent>
void QGVScene::contextMenuEvent(QGraphicsSceneContextMenuEvent *contextMenuEvent)
{
    QGraphicsItem *item = itemAt(contextMenuEvent->scenePos(), QTransform());
    if(item)
    {
        item->setSelected(true);
        if(item->type() == QGVNode::Type)
            emit nodeContextMenu(qgraphicsitem_cast<QGVNode*>(item)->_element);
        else if(item->type() == QGVEdge::Type)
            emit edgeContextMenu(qgraphicsitem_cast<QGVEdge*>(item)->_element);
        else if(item->type() == QGVSubGraph::Type)
            emit subGraphContextMenu(qgraphicsitem_cast<QGVSubGraph*>(item)->_element);
        else
            emit graphContextMenuEvent();
    }
    QGraphicsScene::contextMenuEvent(contextMenuEvent);
}

void QGVScene::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    QGraphicsItem *item = itemAt(mouseEvent->scenePos(), QTransform());
    if(item)
    {
        if(item->type() == QGVNode::Type)
            emit nodeDoubleClick(qgraphicsitem_cast<QGVNode*>(item)->_element);
        else if(item->type() == QGVEdge::Type)
            emit edgeDoubleClick(qgraphicsitem_cast<QGVEdge*>(item)->_element);
        else if(item->type() == QGVSubGraph::Type)
            emit subGraphDoubleClick(qgraphicsitem_cast<QGVSubGraph*>(item)->_element);
    }
    QGraphicsScene::mouseDoubleClickEvent(mouseEvent);
}

#include <QVarLengthArray>
#include <QPainter>
void QGVScene::drawBackground(QPainter * painter, const QRectF & rect)
{
    const int gridSize = 25;

    const qreal left = int(rect.left()) - (int(rect.left()) % gridSize);
    const qreal top = int(rect.top()) - (int(rect.top()) % gridSize);

    QVarLengthArray<QLineF, 100> lines;

    for (qreal x = left; x < rect.right(); x += gridSize)
        lines.append(QLineF(x, rect.top(), x, rect.bottom()));
    for (qreal y = top; y < rect.bottom(); y += gridSize)
        lines.append(QLineF(rect.left(), y, rect.right(), y));

    painter->setRenderHint(QPainter::Antialiasing, false);

    painter->setPen(QColor(Qt::lightGray).lighter(110));
    painter->drawLines(lines.data(), lines.size());
    painter->setPen(Qt::black);
    //painter->drawRect(sceneRect());
}

void QGVScene::add(ManagedElement *p)
{
    _elements.push_front(std::unique_ptr<ManagedElement>(p));
}

void QGVScene::add(ogdf::node x)
{
    add(new QGVNode(this, x, _attributes));
}
void QGVScene::add(ogdf::edge x)
{
    add(new QGVEdge(this, x, _attributes));
}
void QGVScene::add(ogdf::cluster x)
{
    add(new QGVSubGraph(this, x, _attributes));
}
