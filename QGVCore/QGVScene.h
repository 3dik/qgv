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
#ifndef QGVSCENE_H
#define QGVSCENE_H

#include <memory>
#include <forward_list>

#include "qgv.h"
#include "QGVElement.h"

/**
 * @brief OGDF interactive scene
 *
 */
class QGVCORE_EXPORT QGVScene :
    //TODO: GraphObserver & ClusterGraphObserver might make sense
    public QGraphicsScene
{
    Q_OBJECT
public:

    explicit QGVScene(QObject *parent = 0);

    //remove all items and create new ones with the given graph elements
    //
    //All referenced data (attributes, graph etc.) must be alive until this
    //object is destroyed or another data set is load by this method.
    void loadGraph(qgv::all_attributes attributes);
    //set attributes whose values cannot be figured out by ogdf
    void preprocess();
    //apply the layout informations so that we're ready for rendering
    void applyLayout();


signals:
    void nodeContextMenu(ogdf::node node);
    void nodeDoubleClick(ogdf::node node);

    void edgeContextMenu(ogdf::edge edge);
    void edgeDoubleClick(ogdf::edge edge);

    void subGraphContextMenu(ogdf::cluster graph);
    void subGraphDoubleClick(ogdf::cluster graph);

    void graphContextMenuEvent();
    
public slots:

protected:
    virtual void contextMenuEvent(QGraphicsSceneContextMenuEvent * contextMenuEvent);
    virtual void mouseDoubleClickEvent(QGraphicsSceneMouseEvent * mouseEvent);
    virtual void drawBackground(QPainter * painter, const QRectF & rect);

private:

    void add(ManagedElement *);
    void add(ogdf::node);
    void add(ogdf::edge);
    void add(ogdf::cluster);

    qgv::all_attributes _attributes;

    std::forward_list<std::unique_ptr<ManagedElement> > _elements;
};

#endif // QGVSCENE_H
