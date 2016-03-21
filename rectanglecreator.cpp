#include <QtCore/QPointF>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QMainWindow>

#include "graphicsscene.h"
#include "graphicsrectangleitem.h"
#include "graphicsitemcreator.h"
#include "rectanglecreator.h"

/*
	constructor /destructor
*/
RectangleCreator::RectangleCreator()
    :GraphicsItemCreator()
{
    m_rubber_mode = false;
}
RectangleCreator::~RectangleCreator()
{
    
}

void RectangleCreator::paint ( QPainter * painter, const QStyleOptionGraphicsItem* , QWidget* )
{
    if( m_rubber_mode && m_rectangle.isValid() )
    {
	painter->drawRect( m_rectangle );
    }
}

QRectF RectangleCreator::boundingRect () const
{
    return m_rectangle;
}
    
void RectangleCreator::mouseMoveEvent ( QGraphicsSceneMouseEvent * mouseEvent )
{


	QRectF newRect;
	QPointF pt;
	GraphicsScene *pScene;


	pt = mouseEvent->scenePos();
	pScene = dynamic_cast<GraphicsScene*>(scene());
	if( !pScene )
		return;

	pt = pScene->getAlignedPoint(pt);

	if( ! m_rubber_mode )
		return;

	newRect = m_rectangle;

	//change the values of rectangle and point if point is
	//smaller then the origin of rectangle

	if( pt.x() > m_origin.x() )
	{
		newRect.setRight( pt.x() );
		if( ! newRect.isValid() )
		{
			newRect.setLeft( m_origin.x() );
		}
	}
	else
	{
		newRect.setLeft( pt.x() );
		if( ! newRect.isValid() )
		{
			newRect.setRight( m_origin.x() );
		}

	}

	if( pt.y() > m_origin.y() )
	{
		newRect.setBottom( pt.y() );
		if( ! newRect.isValid() )
		{
			newRect.setTop( m_origin.y() );
		}
	}
	else
	{
		newRect.setTop( pt.y() );
		if( ! newRect.isValid() )
		{
			newRect.setBottom( m_origin.y() );
		}
	}



	if( newRect.isValid() )
	{
		prepareGeometryChange();
		m_rectangle = newRect;
		
	}

	mouseEvent->accept();

}
void RectangleCreator::mousePressEvent ( QGraphicsSceneMouseEvent * mouseEvent )
{
    if (mouseEvent->button() == Qt::LeftButton) 
    {
	//first mousepress sets the top left corner of the rectangle
	QPointF pt;
	GraphicsScene *pScene;
	pScene = dynamic_cast<GraphicsScene*>(scene());
	if( pScene == NULL )
	    return;

	pt = mouseEvent->scenePos();
	pt = pScene->getAlignedPoint(pt);

	if( !m_rubber_mode )
	{
	    //set the origin point
	    //and possible smallest rectangle
	    m_rectangle.setLeft( pt.x() );
	    m_rectangle.setTop( pt.y() );
	    m_rectangle.setWidth( pScene->getGridX() ); // if grid is smaller equal one the rectangle is not valid
	    m_rectangle.setHeight( pScene->getGridY() );
	    
	    m_origin = pt;
	    m_rubber_mode = true;
	}
	else
	{
	    if( pt.x() > m_origin.x() )
		m_rectangle.setRight( pt.x() );
	    else
		m_rectangle.setLeft( pt.x() );
	    if( pt.y() > m_origin.y() )
		m_rectangle.setBottom( pt.y() );
	    else
		m_rectangle.setTop( pt.y() );

	    if( m_rectangle.isValid() && pScene != NULL )
	    {
		GraphicsRectangleItem *pItem = new GraphicsRectangleItem(m_rectangle);
		pItem->setFlag( QGraphicsItem::ItemIsSelectable, true );
		pScene->addRCItem((GraphicsItem*) pItem );
		m_rubber_mode = false;
	    }
	}
    }
}

bool RectangleCreator::endCreation()
{
    return true; //do nothing
}
