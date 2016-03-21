#include <QtCore/QObject>
#include <QtCore/QPointF>
#include <QtCore/QString>
#include <QListWidget>
#include <QListWidgetItem>
#include <QtCore/QVector>
#include <QLayout>
#include <math.h>
#include "graphicsscene.h"
#include "snapmode.h"

#include "smgridaligned.h"
#include "smlineend.h"
#include "smgraphicsitem.h"

#include "snapmodes.h"


/*
	constructor /destructor
*/
RCSnapModes::RCSnapModes(QWidget *parent)
{
    //set the default snap mode to null. it will be setted by void RCSnapModes::on_currentIndexChanged(int)
    m_current_snapmode = NULL;

    SnapMode * pItem;
    //creates supported known snapmodes

    pItem = new SMGridAligned;
    m_snapmodes[snap_by_grid] = pItem;
    
    pItem = new SMLineEnd;
    m_snapmodes[snap_by_line_end] = pItem;
    
    pItem = new SMGraphicsItem;
    m_snapmodes[snap_by_item] = pItem;

    m_SnapModeWidget = new QListWidget( parent );
    QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
    sizePolicy1.setHorizontalStretch(0);
    sizePolicy1.setVerticalStretch(0);
    sizePolicy1.setHeightForWidth( parent->sizePolicy().hasHeightForWidth() );
    m_SnapModeWidget->setSizePolicy( sizePolicy1 ); 

    if( parent->layout() != NULL )
    {
	parent->layout()->addWidget( m_SnapModeWidget );
    }

   
    m_SnapModeWidget->addItem( m_snapmodes[snap_by_grid]->getListItem()  );
    m_SnapModeWidget->addItem( m_snapmodes[snap_by_line_end]->getListItem()  );
    m_SnapModeWidget->addItem( m_snapmodes[snap_by_item]->getListItem()  );

}
RCSnapModes::~RCSnapModes()
{
    if( m_SnapModeWidget )
	delete m_SnapModeWidget;
}

QPointF RCSnapModes::getSnapPoint( GraphicsScene *pScene, const QPointF& not_aligned_pt )
{
    QPointF ret_val = not_aligned_pt;
    
    removeSigns();

    for( int i=0; i < m_SnapModeWidget->count(); i++ )
    {
	QListWidgetItem* pItem = m_SnapModeWidget->item(i);
	if( (pItem != NULL) && (pItem->checkState() == Qt::Checked ))
	{
	    bool isvalid;
	    int hash_entry = pItem->data( Qt::UserRole).toInt(&isvalid);
	    if( isvalid )
	    {
		SnapMode * sm = m_snapmodes[(SnapModes)hash_entry];
		if( sm )
		{
		    ret_val = sm->getSnapPoint(pScene, not_aligned_pt);
		    if( ret_val != not_aligned_pt )
		    {
			//first changed point wins, yet
			break;
		    }
		}
	    }
	    //
	}
    }
    return ret_val;
}

void RCSnapModes::removeSigns()const
{
    for( int i=0; i < m_SnapModeWidget->count(); i++ )
    {
	QListWidgetItem* pItem = m_SnapModeWidget->item(i);
	if( (pItem != NULL) )
	{
	    bool isvalid;
	    int hash_entry = pItem->data( Qt::UserRole).toInt(&isvalid);
	    if( isvalid )
	    {
		SnapMode *sm = m_snapmodes[(SnapModes)hash_entry];
		sm->removeSign();
	    }
	}
    }
    
}


/*void RCSnapModes::setWidget( QComboBox* widget)
{
    m_SnapModeWidget = widget;

    if( ! connect( m_SnapModeWidget, SIGNAL( currentIndexChanged(int) ), this, SLOT( on_currentIndexChanged(int) ) ) )
    {
	qDebug( "combox not connected\n" );
    }
    }*/
 /*bool RCSnapModes::fillSnapModes( const supported_snapmodes_t& showSnapModes )
{
    SnapModes current_mode;
    supported_snapmodes_t::const_iterator inx;
    SnapModes sm;
    RCSnapMode * rcsnapmode;
    bool ret_val;
    QVariant data;
    
    if( m_SnapModeWidget == NULL )
	return false;

    if( m_SnapModeWidget->currentIndex() != -1 )
    {
	data = m_SnapModeWidget->itemData( m_SnapModeWidget->currentIndex() );
	current_mode = (SnapModes)data.toInt();
    }
    else
    {
	current_mode = no_snapping;
    }

    m_SnapModeWidget->clear();


    inx = showSnapModes.begin();
    ret_val = (inx != showSnapModes.end() );

    while( inx != showSnapModes.end() )
    {
	
	sm = *inx;
	rcsnapmode = m_snapmodes[sm];
	m_SnapModeWidget->addItem( rcsnapmode->getDescription(), QVariant((int)sm) );
	inx++;
    }
    
    int dataindex = m_SnapModeWidget->findData( QVariant((int)current_mode) );
    if( dataindex != -1 )
	m_SnapModeWidget->setCurrentIndex( dataindex );

    return ret_val;
    }*/

  /*RCSnapMode* RCSnapModes::getUserSelectedSnapMode() 
{
    RCSnapMode * retVal = NULL;

    if( m_SnapModeWidget->currentIndex() == -1 )
	return retVal;
    
    QVariant itemdata = m_SnapModeWidget->itemData( m_SnapModeWidget->currentIndex() );
    SnapModes selected_mode = (SnapModes)itemdata.toInt();
    supported_snapmodeclasses_t::iterator inx;

    inx = m_snapmodes.find( (const SnapModes&) selected_mode );
    if( inx != m_snapmodes.end() )
    {
	retVal =inx.value();
    }
    return retVal;
    }*/

   /*void RCSnapModes::on_currentIndexChanged(int)
{
    RCSnapMode *selected_snapmode;

    selected_snapmode = getUserSelectedSnapMode();
    if( selected_snapmode != m_current_snapmode )
    {
	m_current_snapmode = selected_snapmode;
	emit currentSnapModeChanged( m_current_snapmode );
    }
}
   */
