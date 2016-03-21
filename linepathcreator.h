#ifndef __RCLINEPATHCREATOR_H__
#define __RCLINEPATHCREATOR_H__

#include "graphicsitemcreator.h"

class QMainWindow;
class QEvent;
/** \brief is responsible for creation of RCLinePathItem intances
 *
 */
class LinePathCreator : public GraphicsItemCreator
{
public:
    LinePathCreator();
    ~LinePathCreator();
  

    void mousePressEvent ( QGraphicsSceneMouseEvent * event );
    void mouseMoveEvent ( QGraphicsSceneMouseEvent * event );
    bool endCreation();
    
    mouse_points_t getNodes()const{ return m_points; }
protected:
    void onLeftButtonPressed( QGraphicsSceneMouseEvent * event );

    void paint ( QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget );
    QRectF boundingRect () const;
    QPainterPath shape () const;
	void removeOldGridLine( const QPointF&, const QPointF&, const QPointF&);

    mouse_points_t m_points;
    QPointF m_lastMousePosition;
#ifdef _DEBUG
	QRectF m_clearRect;
#endif
};

#endif //__RCLINEPATHCREATOR_H__
