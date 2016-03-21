#include <QPainter>
#include <QVector2D>
#include <QtCore/QString>
#include <math.h>

#include "graphicsscene.h"
#include "graphicsellipseitem.h"
#include "graphicsrectangleitem.h"

/*
	constructor /destructor
*/
GraphicsRectangleItem::GraphicsRectangleItem ( const QRectF& rectangle, QGraphicsItem * parent, QGraphicsScene * scene )
    :GraphicsItem( parent, scene )
{
    m_rectangle = rectangle;
    m_sType = "circle";
    QString s;
    
   
}

GraphicsRectangleItem::~GraphicsRectangleItem()
{

}

QRectF GraphicsRectangleItem::boundingRect () const
{
    return m_rectangle;
}

void GraphicsRectangleItem::paint( QPainter* painter, const QStyleOptionGraphicsItem * option, QWidget* widget )
{
    if( painter->isActive() )
    {
	painter->save();
	GraphicsItem::paint( painter, option, widget );
	painter->drawRect( boundingRect() );
	painter->restore();
    }

}

mouse_points_t GraphicsRectangleItem::getNodes()const
{
    mouse_points_t points;

    points.push_back( m_rectangle.topLeft() );
    points.push_back( m_rectangle.bottomLeft() );
    points.push_back( m_rectangle.bottomRight() );
    points.push_back( m_rectangle.topRight() );
    points.push_back( m_rectangle.topLeft() );
    return points;
}

mouse_points_t GraphicsRectangleItem::getCenterNodes()const
{
    QPointF pt;
    mouse_points_t points;

    if( m_rectangle.isNull() ) return points;

    qreal width = m_rectangle.topLeft().x()+ m_rectangle.width()/2;
    qreal height = m_rectangle.topLeft().y() + m_rectangle.height()/2;

    points.push_back( QPointF(width, m_rectangle.topLeft().y()  ) );
    points.push_back( QPointF(width, m_rectangle.bottomLeft().y() ) );
    points.push_back( QPointF(m_rectangle.topLeft().x(), height ) );
    points.push_back( QPointF(m_rectangle.topRight().x(), height ) );
    points.push_back( QPointF(width, height) );

    return points;
}

bool GraphicsRectangleItem::getNearestEdgePoint(const QPointF& ptIn, QPointF& ptOut )const
{
    if( (m_rectangle.isNull() ) && (!m_rectangle.isValid()) )
	return false;

    bool ret_value = false;
    qreal smallest_d = 10000000000000.0;


    mouse_points_t points;
    const qreal width = m_rectangle.topLeft().x()+ m_rectangle.width()/2;
    const qreal height = m_rectangle.topLeft().y() + m_rectangle.height()/2;

    
    points.push_back( m_rectangle.topLeft() );
    points.push_back( m_rectangle.bottomLeft() );
    points.push_back( m_rectangle.bottomRight() );
    points.push_back( m_rectangle.topRight() );
    points.push_back( m_rectangle.topLeft() );

    points.push_back( QPointF(width, m_rectangle.topLeft().y()  ) );
    points.push_back( QPointF(width, m_rectangle.bottomLeft().y() ) );
    points.push_back( QPointF(m_rectangle.topLeft().x(), height ) );
    points.push_back( QPointF(m_rectangle.topRight().x(), height ) );
    points.push_back( QPointF(width, height) );

    for( int i=0; i < points.size(); i++)
    {
	QVector2D vec2d(points[i]);
	vec2d -= QVector2D(ptIn);
	qreal length = vec2d.length();
	if( (length < smallest_d ) && (length < getSnapDisctance() ) )
	{
	    ptOut = points[i];
	    smallest_d =length;
	    ret_value = true;
	}
    }

    return ret_value;
}
