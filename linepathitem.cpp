#include <QGraphicsItem>
#include <QPainter>
#include <QMenu>
#include <QGraphicsSceneContextMenuEvent>
#include <QMatrix>
#include <math.h>

#include "global_defs.h"
#include "error.h"
#include "graphicsscene.h"
#include "point.h"
#include "straightline.h"

#include "linepathitem.h"


/*
	constructor /destructor
*/
LinePathItem::LinePathItem( const mouse_points_t& points, QGraphicsItem * parent, QGraphicsScene * scene )
    :GraphicsItem( parent, scene )
{
    setFlag( QGraphicsItem::ItemIsSelectable, true );
    m_points = points;
    m_sType = "line";
}
 
LinePathItem::~LinePathItem()
{
    
}

//overloeded functions
//--------------------------------------------------------
/**
 *
 *It searches for smallest and greates x and y coordinates of points which represent the line path 
*/
QRectF LinePathItem::boundingRect () const
{
    QRectF rc;
    rc = getRectFromPoints();
    qDebug( "QRectF RCLinePathItem::boundingRect () const\n" );
    return rc;
}

/** 
    It paints the lines
 */
void LinePathItem::paint( QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget )
{
    
    if( painter->isActive() )
    {
	qDebug("void RCLinePathItem::paint( QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget )");
	painter->save();
	GraphicsItem::paint( painter, option, widget );
	painter->drawPath( getPaintShape() );
	
	painter->restore();

    }
    
}

QPainterPath LinePathItem::getPaintShape()const
{
    QPainterPath path;
    unsigned long nsize, i;
    QPointF pt;

    nsize = m_points.size();
    if( nsize > 0 )
    {
	pt = m_points[0];
	path.moveTo( pt );
	for( i=1; i < nsize; i++ )
	{
	    pt = m_points[i];
	    path.lineTo( pt );
	}
    }

    return path;
  
}
/**
   Called by paint which passes the returned path to the painter for drawing
   I think this should be changed cause QGraphicsView calls this function to get a
   for the hit test.
 */
QPainterPath LinePathItem::shape() const
{
    QPainterPath path;
    unsigned long nsize, i;
    QPointF pt;
    qDebug( "QPainterPath RCLinePathItem::shape() const\n");
    nsize = m_points.size();
    if( nsize > 0 )
    {
	pt = m_points[0];
	path.moveTo( pt );
	for( i=1; i < nsize; i++ )
	{
	    pt = m_points[i];
	    path.lineTo( pt );
	}
    }
    
    return path;
}
//--------------------------------------------------------
//intern functions
QRectF LinePathItem::getRectFromPoints( ) const
{
    unsigned long i, nsize;
    QPointF pt;
    qreal minx, miny, maxx, maxy;
    QRectF rcReturn;
    
    nsize = m_points.size();
    if( nsize < 1 )
    {
	//init with null values
	minx = miny = maxx = maxy = 0.0;
    }
    else
    {
	//init max and min values with first point
	pt = m_points[0];

	minx = pt.x();
	miny = pt.y();
	maxx = minx;
	maxy = miny;
	
	//go through all other points
	for( i=1; i < nsize; i++)
	{
	    pt= m_points[i];

	    if( pt.x() < minx )
	    {
		minx = pt.x();
	    }
	    else if( pt.x() > maxx )
	    {
		maxx = pt.x();
	    }
	    if( pt.y() < miny )
	    {
		miny = pt.y();
	    }
	    else if( pt.y() > maxy )
	    {
		maxy = pt.y();
	    }

	}
    }
    
    //init the rectangle and return it
    rcReturn.setTopLeft( QPointF( minx, miny) );
    rcReturn.setBottomRight( QPointF( maxx, maxy ) );

    if( (!rcReturn.isNull() ) && ( rcReturn.isEmpty() ) )
    {
	//seems to be a line. set min rectangle
	if( rcReturn.height() <= 0.0 )
	{
	    rcReturn.setBottom( rcReturn.top() +  MIN_RUBBER_RECT_HEIGHT/2 );
	    rcReturn.setTop( rcReturn.top() - MIN_RUBBER_RECT_HEIGHT/2 );
	}

	if( rcReturn.width() <= 0.0 )
	{
	    rcReturn.setRight( rcReturn.left() +  MIN_RUBBER_RECT_WIDTH/2 );
	    rcReturn.setLeft( rcReturn.left() - MIN_RUBBER_RECT_WIDTH/2 );
	}
	
    }
    return rcReturn;
}

mouse_points_t LinePathItem::getCenterNodes()const
{
    mouse_points_t points;
    int size = m_points.size();
    RCPoint pt[3];

    if( size > 1 )
    {
	
	//it is interessting only with more then one point 
	for( int i = size-1; i > 0; i--)
	{
	    pt[1]=m_points[i];
	    pt[0]=m_points[i-1];
	    
	    pt[2] = pt[1].getDirection(pt[0]);
	    double dt = pt[1].getDistance(pt[0]);
	    dt *= 0.5;
	    pt[2] *= dt;
	    pt[2] = pt[1] - pt[2];
	    
	    points.push_back( pt[2] );
	}
    }
    return points;
}

bool LinePathItem::getNearestEdgePoint(const QPointF& ptIn, QPointF& ptOut )const
{
    mouse_points_t points;
    int size = m_points.size();
    RCPoint pt[3];
    bool ret_value = false;
    qreal distance;
    qreal smallest_d = 10000000000000.0;

    points = m_points;
    if( size > 1 )
    {
	
	//it is interessting only with more then one point 
	for( int i = size-1; i > 0; i--)
	{
	    pt[1]=m_points[i];
	    pt[0]=m_points[i-1];
	    
	    pt[2] = pt[1].getDirection(pt[0]);
	    double dt = pt[1].getDistance(pt[0]);
	    dt *= 0.5;
	    pt[2] *= dt;
	    pt[2] = pt[1] - pt[2];
	    
	    points.push_back( pt[2] );
	}

	size = points.size();
	for(int i=0; i < size; i++)
	{
	    pt[0] = points[i];
	    distance = pt[0].getDistance(ptIn);
	    if( (distance < smallest_d) && (distance < EdgeSnap::getSnapDisctance() ) )
	    {
		ptOut = pt[0];
		smallest_d = distance;
		ret_value = true;
	    }
	}
    }
    return ret_value;

}

bool LinePathItem::getNearestLinePoint(const QPointF& ptIn, QPointF& ptOut )const
{
    int size = m_points.size();
    qreal distance;
    qreal smallest_d = 10000000000000.0;
    StraightLine line;
    RCPoint ptCross;

    for( int i=0; i < size-1; i++)
    {
	line.setPoints( m_points[i], m_points[i+1] );
	distance = line.getDistance( ptIn );
	if( distance < smallest_d )
	{
	    smallest_d = distance;
	    ptCross = line.getCrossPoint(ptIn);
	}
    }
    ptOut = ptCross;
    return true;
}

//-------------------------------------------------------------


/*void RCLinePathItem::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
 {
     QMenu menu;
     QAction *removeAction = menu.addAction("Remove");
     QAction *markAction = menu.addAction("Mark");
     QAction *selectedAction = menu.exec(event->screenPos());
     // ...

 }
*/


//int getCrossPoint( const RCPoint& pt1, const RCPoint& pt2, 
