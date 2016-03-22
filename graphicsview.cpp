#include <QMessageBox>
#include <QMouseEvent>
#include <QGraphicsItem>
#include "graphicsscene.h"

#include "graphicsview.h"
#ifdef QT_DEBUG
#include "../build-secondPID-Desktop-Debug/ui_mainwindow.h"
#else
#include "../build-secondPID-Desktop-Release/ui_mainwindow.h"
#endif

GraphicsView::GraphicsView(QWidget *parent)
    : QGraphicsView(parent)
{
    qDebug( ":RCGraphicsView(QWidget *parent)    : QGraphicsView(parent)");
    m_pRubberBand = NULL;
	setMouseTracking(true);
    //setCursor( Qt::CrossCursor );
}

GraphicsView::~GraphicsView()
{
    if( m_pRubberBand != NULL )
    {
	delete m_pRubberBand;
    }
}

void GraphicsView::mousePressEvent(QMouseEvent *event)
{
    if( event->button() == Qt::LeftButton )
    {
	GraphicsScene *pScene = dynamic_cast<GraphicsScene*>(scene());
	if( pScene )
	{
	    if( pScene->isSelectionMode() )
	    {
		if( m_pRubberBand == NULL )
		{
		    m_pRubberBand = new QRubberBand( QRubberBand::Rectangle, this );
		}
		
		m_pRubberBand->setGeometry( QRect(event->pos(), QSize() ) ); //creates an invalid rect
		m_pRubberBand->show();

		return;
	    }
	   
	}
    }
    QGraphicsView::mousePressEvent(event);
}

void GraphicsView::mouseMoveEvent ( QMouseEvent * event )
{
	if( m_pRubberBand && m_pRubberBand->isVisible() )
	{
		m_pRubberBand->setGeometry( QRect(m_pRubberBand->pos(), event->pos()).normalized() );
	}
	else
	{
		QGraphicsView::mouseMoveEvent(event);
	}
}

void GraphicsView::mouseReleaseEvent ( QMouseEvent * event )
{
    if (event->button() == Qt::LeftButton )
    {

	if( m_pRubberBand != NULL)  
	{
	    GraphicsScene* pScene = dynamic_cast<GraphicsScene*>(scene());
	    pScene->clearSelection();
	    
	    QRect rc;
	    if( m_pRubberBand->isVisible() ) 
	    {
		//QPainterPath path;
		//qDebug( "rect is %d,%d,%d,%d", rc.left(), rc.top(), rc.right(), rc.bottom() );
		//path.addRect( rc.normalized() );
		rc = m_pRubberBand->geometry();

		if( ! rc.isValid() )
		{ //is still invalid
		    rc.setLeft( event->x()-5 );
		    rc.setTop( event->y()-5 );
		    rc.setBottom(event->y()+5);
		    rc.setRight(event->x()+5);

		    //m_pRubberBand->setGeometry (rc);
		}
		//pScene->setSelectionArea(path);

		QList<QGraphicsItem*>result = items( rc, Qt::IntersectsItemShape );
		QList<QGraphicsItem*>::iterator it ;
		it = result.begin();
		while( it != result.end() )
		{
		    (*it)->setSelected( true );
		    it++;
		}

		m_pRubberBand->hide();
		return;
	    }
	}
    }
    QGraphicsView::mouseReleaseEvent(event);
}

