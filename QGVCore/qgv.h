#ifndef QGV_H
#define QGV_H

#include <QtGlobal>

#include <ogdf/cluster/ClusterGraphAttributes.h>
#include <ogdf/labeling/ELabelInterface.h>

namespace qgv {
    struct all_attributes {
        ogdf::ClusterGraphAttributes *clusterGraph = 0;
        ogdf::ELabelInterface<double> *edgeLabels = 0;
    };
}

#ifdef QGVCORE_LIB
	#define QGVCORE_EXPORT Q_DECL_EXPORT
#else
	#define QGVCORE_EXPORT Q_DECL_IMPORT
#endif

#endif // QGV_H
