/***************************************************************
QGVCore Sample
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
#include "MainWindow.h"
#include "moc_MainWindow.cpp"
#include "ui_MainWindow.h"
#include <QMessageBox>

#include <ogdf/cluster/ClusterPlanarizationLayout.h>
#include <ogdf/labeling/ELabelPosSimple.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::MainWindow),
    _graph(), _clusterGraph(_graph),
    _attributes(_clusterGraph), _edgeLabels(_attributes)
{
    ui->setupUi(this);
    ui->graphicsView->setScene(&_scene);

    connect(&_scene, SIGNAL(nodeContextMenu(ogdf::node)), SLOT(nodeContextMenu(ogdf::node)));
    connect(&_scene, SIGNAL(nodeDoubleClick(ogdf::node)), SLOT(nodeDoubleClick(ogdf::node)));

    using ogdf::GraphAttributes;
    _attributes.initAtt(
            GraphAttributes::nodeGraphics |
            GraphAttributes::edgeGraphics |
            GraphAttributes::nodeLabel |
            GraphAttributes::edgeLabel |
            GraphAttributes::edgeArrow
            );
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::drawGraph()
{
    using ogdf::node;
    using ogdf::edge;
    using ogdf::cluster;

    //Add some nodes
    node node1 = _graph.newNode();
    setLabel(node1, "BOX");
    node node2 = _graph.newNode();
    setLabel(node2, "SERVER0");
    node node3 = _graph.newNode();
    setLabel(node3, "SERVER1");
    node node4 = _graph.newNode();
    setLabel(node4, "USER");
    node node5 = _graph.newNode();
    setLabel(node5, "SWITCH");

    //Add some edges
    setLabel(_graph.newEdge(node1, node2), "TTL");
    setLabel(_graph.newEdge(node1, node2), "SERIAL");
    setLabel(_graph.newEdge(node1, node3), "RAZ");
    setLabel(_graph.newEdge(node2, node3), "SECU");

    setLabel(_graph.newEdge(node2, node4), "STATUS");

    setLabel(_graph.newEdge(node4, node3), "ACK");

    setLabel(_graph.newEdge(node4, node2), "TBIT");
    setLabel(_graph.newEdge(node4, node2), "ETH");
    setLabel(_graph.newEdge(node4, node2), "RS232");

    setLabel(_graph.newEdge(node4, node5), "ETH1");
    setLabel(_graph.newEdge(node2, node5), "ETH2");

    cluster sgraph = _clusterGraph.createEmptyCluster();
    setLabel(sgraph, "SUB1");

    node snode1 = _graph.newNode();
    setLabel(snode1, "PC0152");
    _clusterGraph.reassignNode(snode1, sgraph);
    node snode2 = _graph.newNode();
    setLabel(snode2, "PC0153");
    _clusterGraph.reassignNode(snode2, sgraph);

    setLabel(_graph.newEdge(snode1, snode2), "RT7");

    setLabel(_graph.newEdge(node3, snode1), "GB8");
    setLabel(_graph.newEdge(node3, snode2), "TS9");

    cluster ssgraph = _clusterGraph.newCluster(sgraph);
    setLabel(ssgraph, "SUB2");

    node ssnode = _graph.newNode();
    setLabel(ssnode, "PC0155");
    _clusterGraph.reassignNode(ssnode, ssgraph);
    setLabel(_graph.newEdge(snode1, ssnode), "S10");

    layout();

    //Fit in view
    ui->graphicsView->fitInView(_scene.sceneRect(), Qt::KeepAspectRatio);
}

void MainWindow::nodeContextMenu(ogdf::node node)
{
    //Context menu exemple
    QMenu menu(_attributes.label(node).c_str());

    menu.addSeparator();
    menu.addAction(tr("Informations"));
    menu.addAction(tr("Options"));

    QAction *action = menu.exec(QCursor::pos());
    if(action == 0)
        return;
}

void MainWindow::nodeDoubleClick(ogdf::node node)
{
    auto str = _attributes.label(node);
    QMessageBox::information(this, tr("Node double clicked"),
                             tr("Node %1").arg(str.c_str()));
}

void MainWindow::layout()
{
    _scene.loadGraph(qgv::all_attributes{&_attributes, &_edgeLabels});
    _scene.preprocess();

    ogdf::ClusterPlanarizationLayout layouter;
    layouter.call(_graph, _attributes, _clusterGraph);

    ogdf::ELabelPosSimple labeller;
    //try not to render directly on the edge, but this won't always work
    labeller.m_edgeDistance = 10;
    labeller.m_midOnEdge = false;
    labeller.call(_attributes, _edgeLabels);

    //Layout scene
    _scene.applyLayout();
}
