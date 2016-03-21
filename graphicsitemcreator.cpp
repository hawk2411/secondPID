#include <QGraphicsScene>
#include <QMainWindow>
//#include "rccreatorwidget.h"
#include "graphicsitemcreator.h"



/*
constructor /destructor
*/
GraphicsItemCreator::GraphicsItemCreator()
{

	/*m_RCCreatorWidget = new RCCreatorWidget( "hallo", dockingstation );
	m_RCCreatorWidget->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea );
	dockingstation->addDockWidget( Qt::LeftDockWidgetArea, m_RCCreatorWidget );
	m_RCCreatorWidget->show();*/


	setAcceptedMouseButtons( Qt::LeftButton|Qt::RightButton );
}
GraphicsItemCreator::~GraphicsItemCreator()
{
	//    m_RCCreatorWidget->close();

	//    delete m_RCCreatorWidget;
}

QRectF GraphicsItemCreator::boundingRect () const
{
	QGraphicsScene * pScene;
	QRectF rcEmpty;

	pScene = scene();
	if( pScene != NULL )
	{
		return pScene->sceneRect();
	}
	else
	{
		return rcEmpty;
	}
}

