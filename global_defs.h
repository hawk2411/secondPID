#ifndef __GLOBAL_DEFS__
#define __GLOBAL_DEFS__

#include <QtCore/QPointF>
#include <QtCore/QVector>

#define MIN_RUBBER_RECT_HEIGHT 10
#define MIN_RUBBER_RECT_WIDTH 10

//Actions
#define ACTION_REMOVE_SELECTION    1001
#define ACTION_SHOWPROPERTY_SELECTION 1002

#define DEF_SNAP_WIDTH 5.0  //< default for snapping distance

/** a vector of 2D scene coordinates
 */
typedef QVector<QPointF> mouse_points_t; 


#endif //__GLOBAL_DEFS__
