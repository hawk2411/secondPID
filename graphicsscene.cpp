#include "global_defs.h"

#include <QGraphicsSceneMouseEvent>
#include <QToolBar>
#include <QMenu>
#include <QPainter>
#include <QRubberBand>
#include <math.h>

#include "snapmodes.h"
#include "graphicsitem.h"

#include "linepathcreator.h"
#include "circlecreator.h"
#include "rectanglecreator.h"

#include "graphicsscenemouseevent.h"
#include "mainwindow.h"

#include "graphicsscene.h"
#ifdef QT_DEBUG
#include "../build-secondPID-Desktop-Debug/ui_mainwindow.h"
#else
#include "../build-secondPID-Desktop-Release/ui_mainwindow.h"
#endif
/*
	constructor /destructor
*/
GraphicsScene::GraphicsScene(QObject *parent)
    : QGraphicsScene(parent)
{
	m_pCreationItem = NULL;
	//m_pRubberRectItem = NULL;
	m_grid_x = 20;
	m_grid_y = 20;
	m_SnapModes = NULL;
	MainWindow *pMainWindow = dynamic_cast<MainWindow*>(parent);
	if(pMainWindow == NULL )
		throw( new RCError(ERR_PARENT_NOT_VALID ) );

	//page_snapmode ist eine Seite innerhalb von dockWidgetCreator

	m_SnapModes = new RCSnapModes(pMainWindow->getUI()->page_snapmode);

}
GraphicsScene::GraphicsScene(  qreal x, qreal y, qreal width, qreal height, QObject * parent)
    :QGraphicsScene( x,y,width,height,parent )
{
	m_pCreationItem = NULL;
	//m_pRubberRectItem = NULL;
	m_grid_x = 20;
	m_grid_y = 20;
	m_SnapModes = NULL;

	MainWindow *pMainWindow = dynamic_cast<MainWindow*>(parent);
	if(pMainWindow == NULL )
		throw( new RCError(ERR_PARENT_NOT_VALID ) );
	m_SnapModes = new RCSnapModes(pMainWindow->getUI()->page_snapmode);
}

GraphicsScene::~GraphicsScene()
{
	if( m_pCreationItem != NULL )
		delete m_pCreationItem;

	//special treatment for RC* items 
	QList<GraphicsItem*>::iterator index;
	GraphicsItem * pItem;

	index = m_ItemsToDelete.begin();
	while( index != m_ItemsToDelete.end() )
	{
		pItem = *index;
		m_ItemsToDelete.removeOne( pItem );
		delete pItem;

		index = m_ItemsToDelete.begin();
    }

}
//-------------------------------------------------------------------------------------------------
/*!
  Die eigentliche Fuktion, die den CreationMode umstellt. 
  @Param
*/
void GraphicsScene::addCreationItem( GraphicsItemCreator * pItem )
{
    
	qDebug( "item set" );
	if( m_SnapModes != NULL )
	{
		m_SnapModes->removeSigns();
	}
	if( m_pCreationItem != pItem )
	{
		//always delete old creation instance
		if( m_pCreationItem != NULL )
		{
			//removeItem( m_pCreationItem );
			delete m_pCreationItem;
			m_pCreationItem = NULL;
		}
		m_pCreationItem = pItem;
		if( m_pCreationItem != NULL )
		{
			addItem( m_pCreationItem );	//inserts a CreationItem in the scene

		}
	}
}

/*
  event functions
 */
void GraphicsScene::contextMenuEvent ( QGraphicsSceneContextMenuEvent * contextMenuEvent )
{
    
	QList<QGraphicsItem*>		sel_items = selectedItems();
	QList<QGraphicsItem*>::iterator	index;
	if( sel_items.size() < 1 )
	{
		QGraphicsScene::contextMenuEvent( contextMenuEvent );
	}
	else
	{
		QMenu	 menu;
		QAction *newAction;

		newAction = menu.addAction( "Remove" );
		newAction->setData( uint(ACTION_REMOVE_SELECTION) );

		newAction = menu.addAction( "Property" );
		newAction->setData( uint(ACTION_SHOWPROPERTY_SELECTION) );

		QAction *selectedAction = menu.exec( contextMenuEvent->screenPos() );
		if( selectedAction != NULL )
		{
			executeAction( selectedAction );
		}
	}

}



void GraphicsScene::mousePressEvent( QGraphicsSceneMouseEvent * mouseEvent )
{
	switch ( mouseEvent->button() )
	{
	case Qt::LeftButton:
		if( m_pCreationItem != NULL )
		{		
			m_pCreationItem->mousePressEvent( mouseEvent );
		}
		break;
	case Qt::RightButton:
		if( m_pCreationItem != NULL )
		{
			m_pCreationItem->endCreation();
			//delete current creation item
			removeItem( m_pCreationItem );
			//set status bar item 
			emit endItemCreation();
		}
		else
		{
			qDebug( "count selected items press: %d", selectedItems().size() );
			mouseEvent->accept();
			//QGraphicsScene::mousePressEvent( mouseEvent );
		}
		break;
	default:
		QGraphicsScene::mousePressEvent( mouseEvent );
		return;
	}
}

void GraphicsScene::mouseMoveEvent ( QGraphicsSceneMouseEvent * mouseEvent )
{
	emit changedCoordinates( mouseEvent->scenePos() );

	if( m_pCreationItem != NULL )
		m_pCreationItem->mouseMoveEvent( mouseEvent );
	//else if( ! increaseRubberRect( mouseEvent ) )
	//QGraphicsScene::mouseMoveEvent( mouseEvent );

	return;
}

void GraphicsScene::mouseReleaseEvent ( QGraphicsSceneMouseEvent * mouseEvent )
{
    switch ( mouseEvent->button() )
    {
	case Qt::LeftButton:
	    //if( ! endRubberRect( ) )
	    //{
		QGraphicsScene::mouseReleaseEvent( mouseEvent );
		//}
	    break;
	default:
	    QGraphicsScene::mouseReleaseEvent( mouseEvent );
	    return;
    }
}
//---------------------------------------------------------------------------------------------

void GraphicsScene::drawBackground ( QPainter *painter, const QRectF & rect )
{
    QGraphicsScene::drawBackground(painter, rect );
    if( painter->isActive() )
    {
	QRectF rc = sceneRect();
	
	painter->drawRect( rc );
	for( qreal y = rc.top(); y < rc.height(); y+=m_grid_y )
	{
	    for( qreal x =rc.left(); x <rc. width(); x+=m_grid_x )
	    {
		painter->drawPoint( x, y );
	    }
	}
    }
}

void GraphicsScene::removeItem(QGraphicsItem * item )
{
    QGraphicsScene::removeItem( item );
    
    
	//special treatment for creation items
	if( item == m_pCreationItem ){
		delete m_pCreationItem;
		m_pCreationItem = NULL;
		return;
	}
	//special treatment for RC* items 
	GraphicsItem* rcitem;
	rcitem = dynamic_cast<GraphicsItem*>(item);
	if( rcitem == NULL )
		return;

	QList<GraphicsItem*>::iterator index;
	index = m_ItemsToDelete.begin();

	while( index != m_ItemsToDelete.end() )
	{
		if( rcitem == *index )
		{
			emit removeRCItem( rcitem );
			qDebug( "after emit\n" );
			m_ItemsToDelete.removeOne( rcitem );
			delete rcitem;
			break;
		}
		index++;
	}
}

void GraphicsScene::addRCItem( GraphicsItem * newItem )
{
    //first add the item into scene
    QGraphicsScene::addItem( newItem );

    //cause this item is created with new it has to be special registared to delete it
    //on remove
    m_ItemsToDelete.push_back( newItem );
    emit newRCItem(newItem);
}
/*
  rubber rect functions
 */
/*bool RCGraphicsScene::startRubberRect( QGraphicsSceneMouseEvent* mouseEvent )
{
    if( mouseEvent->button() == Qt::LeftButton )
    {
	QPointF pt = mouseEvent->scenePos();

	QRectF rubber_rect =  QRectF( pt.x()-MIN_RUBBER_RECT_WIDTH / 2, pt.y()-MIN_RUBBER_RECT_HEIGHT/2, MIN_RUBBER_RECT_WIDTH, MIN_RUBBER_RECT_HEIGHT); //create a small rect
	//m_pRubberRectItem =addRect( rubber_rect );
	return true;
    }
    else
    {
	if( m_pRubberRectItem != NULL )
	    m_pRubberRectItem = NULL;
	return false;
    }
}

bool RCGraphicsScene::increaseRubberRect( QGraphicsSceneMouseEvent* mouseEvent )
{
    if(  m_pRubberRectItem != NULL ) 
    {
	QRectF rubber_rect = m_pRubberRectItem->rect();

	QPointF new_pt = mouseEvent->scenePos();
	qreal dx = fabsf(new_pt.x() - rubber_rect.x());
	qreal dy = fabsf(new_pt.y() - rubber_rect.y());
	if( (dx > MIN_RUBBER_RECT_WIDTH) || (dy > MIN_RUBBER_RECT_HEIGHT) )
	{
	    m_pRubberRectItem->update( rubber_rect );
	    if( dx > MIN_RUBBER_RECT_WIDTH )
	    {
		if( rubber_rect.x() > new_pt.x() ) 
		{
		    rubber_rect.setLeft( new_pt.x() );
		}
		else
		{
		    rubber_rect.setRight( new_pt.x() );
		}
	    }
	    if( dy > MIN_RUBBER_RECT_HEIGHT )
	    {
		if( rubber_rect.y() > new_pt.y() )
		{
		    rubber_rect.setTop( new_pt.y() );
		}
		else
		{
		    rubber_rect.setBottom( new_pt.y() );
		}
	    }
	    m_pRubberRectItem->setRect( rubber_rect );
	    m_pRubberRectItem->update( rubber_rect );
	}

	
	return true;
    }
    else
    {
	return false;
    }
}

bool RCGraphicsScene::endRubberRect()
{
    if( m_pRubberRectItem != NULL ) 
    {
	QPainterPath path;
	path.addRect( m_pRubberRectItem->rect() );
	setSelectionArea( path );
	removeItem( m_pRubberRectItem );
	m_pRubberRectItem = NULL;
	return true;
    }
    else
	return false;
}
*/
//-------------------------------------------------------------------------------------------------

QPointF  GraphicsScene::getAlignedPoint( const QPointF& not_aligned_pt )
{
    QPointF aligned_pt;
    if( m_SnapModes != NULL )
    {
	aligned_pt = m_SnapModes->getSnapPoint( this, not_aligned_pt );
	if( aligned_pt != not_aligned_pt )
	{
	    //shows the new aligned point
	    emit changedCoordinates( aligned_pt );
	}
    }
    else
	aligned_pt = not_aligned_pt;

    return aligned_pt;
}

bool GraphicsScene::executeAction( QAction * toExecute )
{
    bool bRetVal = false;
    uint action_data;

    if( toExecute == NULL )
	return bRetVal;
    
    action_data = toExecute->data().toUInt();
    switch( action_data )
    {
	case ACTION_REMOVE_SELECTION:
	    removeSelectedItems();
	    bRetVal = true;
	    break;
	default:
	    break;
    }

    return bRetVal;
}
/*! 
    calls the function getSnapPoint of current snap mode (user selected)
    can't be const cause getting snappoinnt sets at same time a sign as a
    feedback for the user. The sign is a QGraphicItem and changes the RCScene.
    I'm not content with give the pointer of the caller as parameter which would be changed.
 *
 */

uint GraphicsScene::removeSelectedItems()
{
    QList<QGraphicsItem*> selected_items = selectedItems();
    QList<QGraphicsItem*>::iterator index;
    uint nCount = 0;

    index = selected_items.begin();

    while( index != selected_items.end() )
    {
	removeItem( (*index) );
	index++;
	nCount++;
    }
    
    return nCount;
    
}

/*!
  Called by mainwindow.cpp after user clicked a button to create a grafical item.
*/
bool GraphicsScene::changeCreationMode( CreationModes mode)
{ 
	//we are in creation mode, yet
	GraphicsItemCreator *pNewCreator = NULL;
	switch( mode )
	{
	case None:
		addCreationItem(pNewCreator);
		break;
	case Path:
		pNewCreator = new LinePathCreator();
		if( pNewCreator == NULL )
		{
			throw new RCError(ERR_MEMORY);
		}
		addCreationItem( pNewCreator );
		break;
	case Circle:
		pNewCreator = new CircleCreator();
		if( pNewCreator == NULL )
		{
			throw new RCError(ERR_MEMORY);
		}
		addCreationItem( pNewCreator );
		break;
	case Rectangle:
		pNewCreator = new RectangleCreator();
		if( pNewCreator == NULL )
		{
			throw new RCError(ERR_MEMORY);
		}
		addCreationItem( pNewCreator );
		break;
	default:

		break;
	}
	return true; 
}
