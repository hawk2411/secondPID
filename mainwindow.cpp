#include <QMessageBox>
#include <QGraphicsItem>
#include <QComboBox>


#define _USE_MATH_DEFINES
#include <math.h>

#include "global_defs.h"
#include "snapmodes.h"
#include "graphicsscene.h"
#include "graphicsstyle.h"
#include "graphicsview.h"
#include "graphicsitem.h"

#include "mainwindow.h"
#ifdef QT_DEBUG
#include "../build-secondQ5-Desktop-Debug/ui_mainwindow.h"
#else
#include "../build-secondQ5-Desktop-Release/ui_mainwindow.h"
#endif


MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent), m_ui(new Ui::MainWindowClass)
{
	m_ui->setupUi(this);
	m_pGraphicsView =m_ui->graphicsView;
	if( m_pGraphicsView == NULL )
		qDebug( "is null" );
	m_pGraphicsTreeView =  m_ui->treeView;
	if( m_pGraphicsTreeView == NULL )
		qDebug( "tree view is null" );

	m_pScene = new GraphicsScene(0.0,0.0,1024.0,768.0, this);

	connect( m_pScene, SIGNAL(endItemCreation()), m_ui->actionSelectGraphObject, SLOT(trigger() ) );
	m_pGraphicsView->setScene( m_pScene );

	if( ! connect( m_pScene, SIGNAL(newRCItem(GraphicsItem*)), m_pGraphicsTreeView, SLOT(on_NewRCGraphicsItem(GraphicsItem*)) ) )
	{
		qDebug( "not connected\n" );
	}
	if( ! connect( m_pScene, SIGNAL(removeRCItem(GraphicsItem*)), m_pGraphicsTreeView, SLOT(on_RemoveRCGraphicsItem(GraphicsItem*)) ) )
	{
		qDebug( "not connected\n" );
	}


	//this widget will set visible if a create class need it
	//m_ui->dockWidgetCreator->setVisible(false);

	m_orthCoordinate.setText( "222.222 333.222" );
	m_polarCoordinate.setText( "300,444 43°" );

	m_ui->statusBar->addPermanentWidget( &m_orthCoordinate );
	m_ui->statusBar->addPermanentWidget( &m_polarCoordinate );

	if( ! connect( m_pScene, SIGNAL( changedCoordinates( const QPointF&) ), this, SLOT( on_showCoordinate(const QPointF&) ) ) )
	{
		qDebug( "changeCoordinates not connected" );
	}

}

MainWindow::~MainWindow()
{
	delete m_pGraphicsTreeView;
	delete m_pScene;
	delete m_ui;
}


void MainWindow::on_actionSelectGraphObject_triggered()
{
	qDebug( "void MainWindow::on_actionSelectGraphObject_triggered()");
	if( m_ui->actionSelectGraphObject->isChecked() )
	{
		synchronizeToolBar( m_ui->drawToolBar, m_ui->actionSelectGraphObject );
		m_pScene->addCreationItem( NULL );
		m_ui->dockWidgetCreator->setVisible(true);
		m_ui->dockWidgetCreator->setVisible(true);
	}
}

void MainWindow::on_actionAddLine_triggered()
{
	if( m_ui->actionAddLine->isChecked() )
	{
		qDebug( "void MainWindow::on_actionAddLine_triggered()");
		synchronizeToolBar( m_ui->drawToolBar, m_ui->actionAddLine );

		//switch to create line mode

		m_pScene->changeCreationMode( Path );
		//m_pScene->addCreationItem( pLineCreator );
		m_ui->dockWidgetCreator->setVisible(true);

	}
}

void MainWindow::on_actionAddCircle_triggered()
{
	qDebug( "void MainWindow::on_actionAddCircle_triggered()");
	if( m_ui->actionAddCircle->isChecked() )
	{
		synchronizeToolBar( m_ui->drawToolBar, m_ui->actionAddCircle );

		//	RCCircleCreator *pCircleCreator = new RCCircleCreator();
		//	m_pScene->addCreationItem(pCircleCreator);
		m_pScene->changeCreationMode(Circle);
		m_ui->dockWidgetCreator->setVisible(true);
	}
}

void MainWindow::on_actionAddRectangle_triggered()
{
	qDebug( "void MainWindow::on_actionAddRectangle_triggered()");
	if( m_ui->actionAddRectangle->isChecked() )
	{
		synchronizeToolBar( m_ui->drawToolBar, m_ui->actionAddRectangle );

		//	RCRectangleCreator *pRectangleCreator = new RCRectangleCreator();
		//	m_pScene->addCreationItem(pRectangleCreator);
		m_pScene->changeCreationMode(Rectangle);
		m_ui->dockWidgetCreator->setVisible(true);
	}
}

void MainWindow::on_actionAddText_triggered()
{
	qDebug( "void MainWindow::on_actionAddText_triggered");
	if( m_ui->actionAddText->isChecked() )
	{
		synchronizeToolBar( m_ui->drawToolBar, m_ui->actionAddText );

		m_pScene->changeCreationMode(Rectangle);
		m_ui->dockWidgetCreator->setVisible(true);
	}

}

long MainWindow::synchronizeToolBar( QToolBar * pToSynchronize, QAction * pTriggered )
{
	/*
	go through the list of actions of the given toolbar and check or uncheck
	all buttons that are not triggered
	*/
	QList<QAction*> list_of_actions;
	QList<QAction*>::iterator index;
	QAction* pAction;
	long count_changed_actions = 0;

	list_of_actions = pToSynchronize->actions(); //gets the list of action
	if( list_of_actions.size() < 1 ) return 0; // no action there

	if( pTriggered->isCheckable() ){ // it just works if the triggered action is checkable
		index = list_of_actions.begin(); //got to start of the list
		while( index != list_of_actions.end() ){
			pAction = *index;

			if( pAction != pTriggered ){
				if( pAction->isCheckable() ){
					if( pAction->isChecked() == pTriggered->isChecked() ){
						pAction->setChecked( ! pTriggered->isChecked() );
						count_changed_actions++; //increment the return value
					}
				}
			}

			index++;
		}

	}
	return count_changed_actions;
}
void MainWindow::on_showCoordinate( const QPointF& pt )
{

	QString s;

	//kartesisch
	s= QString("x: %1 | ").arg(pt.x(), 0, 'f', 3);
	s+= QString("y: %1").arg(pt.y(), 0, 'f', 3);

	m_orthCoordinate.setText( s );

	//polar
	qreal radius, power, phi;
	power = pow( pt.x(), 2 ) + pow( pt.y(), 2 );
	if( power > 0.0 )
	{
		radius = sqrt( power );
		phi = atan2( pt.x(), pt.y() );
		s=QString( "Radius: %1 | ").arg(radius, 0, 'f', 3);
		s+= QString("Angle: %1").arg(phi*180.0/M_PI,0,'f',3);
		m_polarCoordinate.setText( s );
	}
}

void MainWindow::on_actionScalePlus_triggered()
{
	m_pGraphicsView->scale( 2,2);
}

void MainWindow::on_actionScaleMinus_triggered()
{
	m_pGraphicsView->scale( 0.5,0.5);
}


/*void MainWindow::clicked( const QModelIndex& index)
{
	QStandardItemModel* graphicsItemModel =	dynamic_cast<QStandardItemModel*>(m_pGraphicsTreeView->model());
	QStandardItem* clickedItem = graphicsItemModel->itemFromIndex( index );

	QVariant var = clickedItem->data(RCGraphicsTreeView::MyClassRole);
	RCGraphicsItem* graphicItem = (RCGraphicsItem*)var.value<int>();		
	
	graphicItem->setSelected(true);
}*/
