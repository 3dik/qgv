#-------------------------------------------------
#
# Project created by QtCreator 2013-04-17T09:06:06
#
#-------------------------------------------------

QT       += core

greaterThan(QT_MAJOR_VERSION, 4){
    QT += widgets
}
lessThan(QT_MAJOR_VERSION, 5) {
    QT += gui
}

TARGET = QGVCore
TEMPLATE = lib
CONFIG += shared

DESTDIR = ../lib
DLLDESTDIR = ../bin

#GraphViz librairie
!include(GraphViz.pri) {
     error("fail open GraphViz.pri")
 }

SOURCES += QGVScene.cpp \
    QGVNode.cpp \
    QGVEdge.cpp \
    QGVSubGraph.cpp \
		private/QGVCore.cpp \

HEADERS  += QGVScene.h \
    QGVElement.h \
    QGVNode.h \
    QGVEdge.h \
    QGVSubGraph.h \
		private/QGVCore.h \
    qgv.h
