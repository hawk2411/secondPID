#include <math.h>

#include <QGraphicsItem>
#include <QListWidgetItem>

#include "graphicsscene.h"

#include "snapmode.h"


/*
	constructor /destructor
*/
SnapMode::SnapMode()
{
    m_Description = "no snapping";
    m_SnappingSign = NULL;
    m_ListItem = NULL;
    m_ListItem = new QListWidgetItem;
    m_ListItem->setText( m_Description );

}
SnapMode::~SnapMode()
{
    delete m_ListItem;
}

QPointF SnapMode::getSnapPoint( GraphicsScene *, const QPointF& not_aligned_pt )
{
    //do nothing and return the given paramter unchanged
    return not_aligned_pt;
   
}

void SnapMode::setDescription( const QString& sNewDescription )
{
    m_Description = sNewDescription;
    m_ListItem->setText( sNewDescription );
}

QListWidgetItem* SnapMode::getListItem()const
{
    return m_ListItem;
}
void SnapMode::removeSign()
{

    if( m_SnappingSign != NULL ) 
    {
	QGraphicsScene * scene = m_SnappingSign->scene();
	if( scene )
	{
	    scene->removeItem( m_SnappingSign );
	    m_SnappingSign = NULL;
	}
    }
}
