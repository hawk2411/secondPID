#ifndef __RCGRAPHICSRECTANGLEITEM_H__
#define __RCGRAPHICSRECTANGLEITEM_H__

#include "graphicsitem.h"


class GraphicsRectangleItem : public GraphicsItem,
    public EdgeSnap
{
    //constructor/destructor
public:
    GraphicsRectangleItem ( const QRectF& rectangle, QGraphicsItem * parent = 0, QGraphicsScene * scene = 0 );
    ~GraphicsRectangleItem();

    //overloaded functions
protected:
    void paint( QPainter* painter, const QStyleOptionGraphicsItem*, QWidget* =0 ); 
    QRectF boundingRect () const;

    //members access functions
public:
    void setRectangle( const QRectF& rec ){ m_rectangle = rec; }
    QRectF getRectangle()const{ return m_rectangle; }

    bool getNearestEdgePoint(const QPointF& ptIn, QPointF& ptOut )const; 

    mouse_points_t getNodes()const;
    mouse_points_t getCenterNodes()const;

    //Members
private:
    QRectF  m_rectangle;
};

#endif //__RCGRAPHICSRECTANGLEITEM_H__
