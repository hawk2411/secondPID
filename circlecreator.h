#ifndef __RCCIRCLECREATOR_H__
#define __RCCIRCLECREATOR_H__

#include <QRectF>
#include "graphicsitemcreator.h"
/** \brief this class capsulates the creating of circles
 *
 */
class CircleCreator : public GraphicsItemCreator
{
public:
    CircleCreator();
    ~CircleCreator();

    void paint ( QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = 0 );
    QRectF boundingRect () const;
    
    void mouseMoveEvent ( QGraphicsSceneMouseEvent * mouseEvent );
    void mousePressEvent ( QGraphicsSceneMouseEvent * mouseEvent );
    bool endCreation();
protected:

private:
    QRectF m_rectangle;
    QPointF m_origin;
    bool m_rubber_mode;
};

#endif //__RCCIRCLECREATOR_H__

