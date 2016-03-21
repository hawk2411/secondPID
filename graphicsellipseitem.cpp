#include <QPainter>
#include <QString>
#include <math.h>
#include "graphicsscene.h"
#include "graphicsellipseitem.h"


/*
	constructor /destructor
*/
GraphicsEllipseItem::GraphicsEllipseItem ( const QRectF& rectangle, QGraphicsItem * parent, QGraphicsScene * scene )
    :GraphicsRectangleItem( rectangle, parent, scene )
{
    m_rectangle = rectangle;
    m_sType = "circle";
    QString s;
    
   
}

GraphicsEllipseItem::~GraphicsEllipseItem()
{

}

QRectF GraphicsEllipseItem::boundingRect () const
{
    return m_rectangle;
}

void GraphicsEllipseItem::paint( QPainter* painter, const QStyleOptionGraphicsItem * option, QWidget * widget )
{
	if( painter->isActive() )
	{
		painter->save();
		GraphicsItem::paint( painter, option, widget );
		painter->drawEllipse( boundingRect() );
		painter->restore();
	}

}

/*mouse_points_t RCGraphicsEllipseItem::getNodes()const
{
    mouse_points_t points;

    points.push_back( m_rectangle.topLeft() );
    points.push_back( m_rectangle.bottomLeft() );
    points.push_back( m_rectangle.topRight() );
    points.push_back( m_rectangle.bottomRight() );
    
    return points;
}
*/
bool GraphicsEllipseItem::collidesWithPath ( const QPainterPath & path, Qt::ItemSelectionMode ) const
{
    return intersects(path.boundingRect());
}

bool GraphicsEllipseItem::intersects(QRectF rc )const
{
	if( ! m_rectangle.isValid() )
		return false;
	if( ! rc.isValid() )
		return false;

	if( ! intersects( rc.topLeft(), rc.bottomRight() ) )
	{
		return intersects(rc.topRight(), rc.bottomLeft() );
	}
	else
	{
		return true;
	}

}

bool GraphicsEllipseItem::intersects( QPointF p1, QPointF p2 )const
{
	qreal w = m_rectangle.width()/2;
	qreal h = m_rectangle.height()/2;
	QPointF middle( m_rectangle.left()+w, m_rectangle.top()+h );

	qreal rrx = w*w; qreal rry = h*h;
	QPointF pt_dir = p2-p1;
	QPointF p10 = p1 - middle;
	qreal a = pow(pt_dir.x(),2)/rrx + pow(pt_dir.y(),2)/rry;
	qreal b = pt_dir.x()*p10.x()/rrx + pt_dir.y()*p10.y()/rry;
	qreal c = pow(p10.x(),2)/rrx + pow(p10.y(),2)/rry;
	qreal d = b*b-a*(c-1);
	if( d >= 0 )
	{
		qreal e = sqrt(d);
		qreal u1 = (-b-e)/a;
		qreal u2 = (-b+e)/a;
		if( u1 >= 0.0 && u1 <= 1.0 )
		{
			return true;
		}
		if( u2 >= 0.0 && u2 <= 1.0 )
		{
			return true;
		}
	}
	return false;
}
