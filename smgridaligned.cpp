#include <QtCore/QPointF>
#include <QListWidgetItem>
#include <QGraphicsItem>
#include <math.h>
#include "graphicsscene.h"
#include "snapmodes.h"

#include "smgridaligned.h"


/*
	constructor /destructor
*/
SMGridAligned::SMGridAligned()
{
    m_Description = "grid align";

    m_ListItem->setText( m_Description );
    m_ListItem->setFlags( Qt::ItemIsSelectable|Qt::ItemIsUserCheckable|Qt::ItemIsEnabled);
    m_ListItem->setCheckState( Qt::Unchecked );
    m_ListItem->setData( Qt::UserRole, QVariant((int)snap_by_grid));
}
SMGridAligned::~SMGridAligned()
{
}

QPointF SMGridAligned::getSnapPoint( GraphicsScene * scene, const QPointF& not_aligned_pt )
{
    QPointF aligned_pt;
    aligned_pt = not_aligned_pt;
    qreal gridx, gridy;

    gridx = scene->getGridX();
    gridy = scene->getGridY();

    if( gridx == 0 || gridy == 0 )
	return aligned_pt;

    qreal x = aligned_pt.x();
    qreal y = aligned_pt.y();
    qreal dx = x / gridx;
    qreal dy = y / gridy;
    double ip_x, ip_y;
    double mod_x = modf(dx, &ip_x);
    double mod_y = modf(dy, &ip_y);

    if( ! mod_x )
	aligned_pt.setX(x);
    else 
    {
	if( mod_x >= 0.5 )
	    aligned_pt.setX( ip_x * gridx + gridx );
	else
	    aligned_pt.setX( ip_x * gridx );
    }
    if( ! mod_y )
	aligned_pt.setY(y);
    else 
    {
	if( mod_y >= 0.5 )
	    aligned_pt.setY( ip_y * gridy + gridy );
	else
	    aligned_pt.setY( ip_y * gridy );
    }
    
    if( aligned_pt != not_aligned_pt )
    {
	setSign( scene, aligned_pt );
    }
    else
    {
	removeSign();
    }
    return aligned_pt;
   
}

void SMGridAligned::setSign( GraphicsScene* scene, const QPointF& nearest_point )
{
    QRectF rc( nearest_point.x()-10, nearest_point.y()-10, 20, 20 );
    
    if( ( m_SnappingSign != NULL ) &&  (m_SnappingSign->boundingRect() != rc) )
    {
	removeSign();
    }
    if( m_SnappingSign == NULL )
    {
	QPainterPath path( rc.topLeft() );
	path.lineTo( rc.bottomRight() );
	path.moveTo( rc.topRight() );
	path.lineTo( rc.bottomLeft() );

	m_SnappingSign = scene->addPath( path );
    }
    
}
