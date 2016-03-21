#ifndef __RCGRAPHICSELLIPSEITEM_H__
#define __RCGRAPHICSELLIPSEITEM_H__

//#include "rcgraphicsitem.h"
#include "graphicsrectangleitem.h"

class GraphicsEllipseItem : public GraphicsRectangleItem
{
    //constructor/destructor
public:
    GraphicsEllipseItem ( const QRectF& rectangle, QGraphicsItem * parent = 0, QGraphicsScene * scene = 0 );
    ~GraphicsEllipseItem();

    //overloaded functions
protected:
    void paint( QPainter* painter, const QStyleOptionGraphicsItem * option, QWidget * widget = 0 ); 
    QRectF boundingRect () const;
    bool collidesWithPath ( const QPainterPath & path, Qt::ItemSelectionMode) const;

    
    //members access functions
public:
    void setRectangle( const QRectF& rec ){ m_rectangle = rec; }
    QRectF getRectangle()const{ return m_rectangle; }

    bool intersects(QRectF rc )const;
    bool intersects( QPointF p1, QPointF p2 )const;

    //mouse_points_t getNodes()const;
    //Members
private:
    QRectF  m_rectangle;
};

#endif //__RCGRAPHICSELLIPSEITEM_H__
