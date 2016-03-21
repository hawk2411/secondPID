#ifndef __RCLINEPATHITEM_H__
#define __RCLINEPATHITEM_H__

#include "graphicsitem.h"

/*! \brief Represents a 2D line or a line path

  RCLinePath conctructs line paths.
*/
class LinePathItem : public GraphicsItem,
    public EdgeSnap,
    public LineSnap
{
public:
    //constructor and desctrutor
    LinePathItem ( const mouse_points_t& points, QGraphicsItem * parent = 0, QGraphicsScene * scene = 0 );
    ~LinePathItem();

    //overloadded functions
public:
    bool getNearestEdgePoint(const QPointF& ptIn, QPointF& ptOut )const; 
    bool getNearestLinePoint(const QPointF& ptIn, QPointF& ptOut )const;
protected:
    ///derived function from RCGraphicsItem -> QGraphicsItem. 
    QRectF boundingRect () const;


    ///derived from QGraphicsItem
    void paint( QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = 0 );

    ///derived from QGraphicsItem
    QPainterPath shape() const;

    QPainterPath getPaintShape()const;
    
    ///returns the nodes of the path which are stored in m_points;
    mouse_points_t getNodes()const{ return m_points; }

    ///returns the nodes of the middle 
    mouse_points_t getCenterNodes()const;

//    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);
    
    //members access functions
public:
    void setPoints( const mouse_points_t& points ){ m_points = points; }
    mouse_points_t getPoints()const{ return m_points; }

    //Members
private:
    mouse_points_t m_points; //!< 2D points in scene coordinate

    //intern functions
protected:
    QRectF getRectFromPoints( )const;
};

#endif //__RCLINEPATHITEM_H__
