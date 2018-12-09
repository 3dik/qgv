#ifndef GRAPHELEMENT_H
#define GRAPHELEMENT_H

#include "qgv.h"

#include <QGraphicsScene>
#include <QGraphicsItem>

/* generic interface for the drawing of a graph element
 */
struct ManagedElement : public QGraphicsItem
{
    virtual void preprocess() =0;
    virtual void updateLayout() =0;
};

/* drawing of a single graph element, e.g. node or edge
 *
 * ELEMENT must be the element type and its attributes should be accessible
 * through ClusterGraphAttributes.
 * USERTYPE: see qt docs
 */
template <typename ELEMENT, unsigned int USERTYPE>
struct GraphElement : public ManagedElement
{
    GraphElement(QGraphicsScene *parent, ELEMENT e, qgv::all_attributes attr) :
        _element(e), _attributes(attr), _parent(*parent)
    {
        _parent.addItem(this);
    }

    enum { Type = UserType + USERTYPE };
    int type() const
    {
        return Type;
    }

    const ELEMENT _element;

protected:

    QString label() const
    {
        return _attributes.clusterGraph->label(_element).c_str();
    }
    const qgv::all_attributes _attributes;

private:

    QGraphicsScene &_parent;

};

#endif
