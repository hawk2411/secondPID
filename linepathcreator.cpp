#include <Qt>
#include <QtCore/QEvent>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsItem>
#include <QtCore/QVector>
#include <QPainter>
#include <QGraphicsScene>
#include <QPainterPath>
#include <QGraphicsView>
#include <QtCore/QPointF>
#include <QMainWindow>
#include <math.h>

#include "global_defs.h"
#include "error.h"
#include "graphicsscene.h"
#include "linepathcreator.h"
#include "linepathitem.h"

/*
  constructor /destructor
*/
LinePathCreator::LinePathCreator()
	:GraphicsItemCreator()
{
}
LinePathCreator::~LinePathCreator()
{
}

void LinePathCreator::onLeftButtonPressed( QGraphicsSceneMouseEvent * event )
{
	QPointF pt = event->scenePos( );
	QRectF rc;

	GraphicsScene* pScene = dynamic_cast<GraphicsScene*>(scene());

	if( pScene != NULL )
	{
		pt = pScene->getAlignedPoint(pt);
	}

	prepareGeometryChange();
	m_points.push_back(pt);

	if( m_points.size() == 1 )
	{
		m_lastMousePosition = pt;   //init last pos at same position
	}
	rc = boundingRect();
	update(rc);

}


void LinePathCreator::mouseMoveEvent ( QGraphicsSceneMouseEvent * event ) 
{
	GraphicsScene *pScene;

	pScene = dynamic_cast<GraphicsScene*>(scene());
	if( pScene == NULL )
	{
		event->ignore();
		return;
	}

	if( m_points.size() == 0 )
	{
		QPointF aligned_pt;

		aligned_pt =pScene->getAlignedPoint( event->scenePos() );
		if( aligned_pt != event->scenePos() )
		{
			//point has been aligned
			//TODO for convenience it were helpful to change the cursor
		}
	}
	else
	{
		
		//update( boundingRect() );
		QPointF newMousePos = pScene->getAlignedPoint( event->scenePos() );
		QPointF point = m_lastMousePosition - newMousePos;
		if( point.manhattanLength() > 0 )
		{
			//refresh old lines and delete old rubber line
			prepareGeometryChange();
			m_lastMousePosition = newMousePos;
		}
	}
}
/**
   called from RCGraphic
*/
void LinePathCreator::mousePressEvent ( QGraphicsSceneMouseEvent * event )
{

	switch ( event->button() )
	{
	case Qt::LeftButton:
		onLeftButtonPressed( event );
		break;
	default:
		break;
	}
}


void LinePathCreator::paint ( QPainter * painter, const QStyleOptionGraphicsItem *, QWidget* )
{
	painter->setBackgroundMode(Qt::OpaqueMode);
	if( painter->isActive() )
	{
		QPainterPath path;

		//qDebug( "boundRectleft %f, boundRecttop %f, boundRectright %f, boundRectbottom %f\n", boundRect.left(), boundRect.top(), boundRect.right(), boundRect.bottom());

		if(m_points.size() == 0) return;

		QPointF pt = m_points[0];
		path.moveTo( pt.x(), pt.y() );

		for( long i=1; i < m_points.size(); i++)
		{
			pt = m_points[i];
			path.lineTo( pt.x(), pt.y() );
		}
		path.lineTo( m_lastMousePosition.x(), m_lastMousePosition.y() );
		painter->drawPath( path );

#ifdef _DEBUG
		//painter->drawRect(m_clearRect);
#endif
	}

}

QRectF LinePathCreator::boundingRect () const
{
	QPointF pt;
	QRectF rc;
	qreal min_x, min_y, max_x, max_y, x, y;
	mouse_points_t points;

	points = m_points;

	min_x = min_y = max_x = max_y = HUGE_VAL;


	if( m_points.size() > 0 )
	{
		points.push_back( m_lastMousePosition );
	}
	if( points.size() > 0 )
	{
		for( long i = 0; i < points.size(); i++ )
		{
			pt = points[i];

			x = pt.x();
			y = pt.y();

			if( ( min_x == HUGE_VAL ) || ( x < min_x ) )
				min_x = x;
			if( ( max_x == HUGE_VAL ) || ( x > max_x ) )
				max_x = x;

			if( ( min_y == HUGE_VAL ) || ( y < min_y ) )
				min_y = y;
			if( ( max_y == HUGE_VAL ) || ( y > max_y ) )
				max_y = y;
		}
		rc.setLeft( min_x );
		rc.setTop( min_y );
		rc.setBottom( max_y );
		rc.setRight( max_x );
	}
	else 
	{
		rc.setLeft( 0.0  );
		rc.setTop( 0.0 );
		rc.setRight(rc.left()+1.0 );
		rc.setBottom(rc.top()+1.0 );

	}
	return rc;
}

QPainterPath LinePathCreator::shape () const 
{
	QPainterPath path;

	if( m_points.size() > 1) 
	{
		QPointF pt;

		for( long i=0; i < m_points.size(); i++)
		{
			pt = m_points[i];
			if( i == 0 )
			{
				path.moveTo( pt.x(), pt.y() );
			}
			else
			{
				path.lineTo( pt.x(), pt.y() );
			}
		}
	}
	return path;
}


bool LinePathCreator::endCreation()
{
	if( (scene() != NULL ) && (m_points.size() > 1 ) )
	{
		LinePathItem *newItem;
		GraphicsScene *pScene = dynamic_cast<GraphicsScene*>(scene());

		newItem = new LinePathItem( m_points );
		if( (newItem != NULL) && (pScene !=NULL ) )
		{
			pScene->addRCItem( (GraphicsItem*)newItem );
			return true;
		}
	}
	return false;
}

void LinePathCreator::removeOldGridLine( const QPointF& lastMousePos, const QPointF& newMousePos, const QPointF& lastPathPoint )
{
	QPointF points[3] = {lastMousePos, newMousePos, lastPathPoint};

	QRectF rc;
	rc.setX(lastMousePos.x());
	rc.setY( lastMousePos.y() );
	rc.setRight(lastMousePos.x());
	rc.setBottom(lastMousePos.y());
	for( int i=0; i < 3; i++)
	{
		if( points[i].x() < rc.left() )
		{
			rc.setLeft(points[i].x() - 10.f );
		}
		if( points[i].y() < rc.top()  )
		{
			rc.setTop(points[i].y()- 10.f);
		}
		if( points[i].x() > rc.right() )
		{
			rc.setRight(points[i].x()+ 10.f );
		}
		if( points[i].y() > rc.bottom() )
		{
			rc.setBottom(points[i].y() + 10.f);
		}
	}
#ifdef _DEBUG
	m_clearRect = rc;
#endif
	qDebug( "rc.left %f, rc.top %f, rc.right %f, rc.bottom %f\n", rc.left(), rc.top(), rc.right(), rc.bottom());
	update(rc);
}


