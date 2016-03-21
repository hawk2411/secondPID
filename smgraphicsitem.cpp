#include <QtCore/QRectF>
#include <QGraphicsItem>
#include <QListWidgetItem>
#include <math.h>

#include "global_defs.h"
#include "graphicsitem.h"
#include "graphicsscene.h"
#include "snapmodes.h"

#include "smgraphicsitem.h"


/*
	constructor /destructor
*/
SMGraphicsItem::SMGraphicsItem()
{
    m_snapDistance = DEF_SNAP_WIDTH;
    m_Description = "items";

    //m_ListItem = new QListWidgetItem;
    m_ListItem->setText( m_Description );
    m_ListItem->setFlags( Qt::ItemIsSelectable|Qt::ItemIsUserCheckable|Qt::ItemIsEnabled);
    m_ListItem->setCheckState( Qt::Unchecked );
    m_ListItem->setData( Qt::UserRole, QVariant((int)snap_by_item));

}
SMGraphicsItem::~SMGraphicsItem()
{

}
QPointF SMGraphicsItem::getSnapPoint( GraphicsScene * scene, const QPointF& not_aligned_pt )
{
    const int rect_width = m_snapDistance;
    const double half = rect_width/2;
    

    
    QPointF nearest_point;
    qreal smallest_d = 10000000000000.0;
    //construct a square
    QRectF rc(
	QPointF(not_aligned_pt.x() - half, not_aligned_pt.y() -half),
	QSizeF(rect_width, rect_width)
	);
    
    //get items intersect the rectangle
    QList<QGraphicsItem*> litems = scene->items( rc );

    for( int i=0; i < litems.size(); i++)
    {
	GraphicsItem *item = dynamic_cast<GraphicsItem*>(litems[i]);
	if( item != NULL )
	{
	    LineSnap *line_snap = dynamic_cast<LineSnap*>(item);
	    if( line_snap )
	    {
		QPointF item_nearest_point;
		if( line_snap->getNearestLinePoint( not_aligned_pt, item_nearest_point ) ) //TODO change the out parameter from reference to pointer
		{
		    qreal d = RCPoint(item_nearest_point).getDistance( not_aligned_pt );
		    if( d < smallest_d )
		    {
			smallest_d = d;
			nearest_point = item_nearest_point;
		    }
		}
	    }
	}
    }

    if( ! nearest_point.isNull() )
    {
	setSign( scene, nearest_point );
	return nearest_point;
    }
    removeSign();
    return not_aligned_pt;
}

void SMGraphicsItem::setSign( GraphicsScene* scene, const QPointF& nearest_point )
{
    QRectF rc( nearest_point.x()-10, nearest_point.y()-10, 20, 20 );

    if( ( m_SnappingSign != NULL ) &&  (m_SnappingSign->boundingRect() != rc) )
    {
	removeSign();
	m_SnappingSign = scene->addRect( rc );
    }
    else if( m_SnappingSign == NULL )
    {
	qDebug( "set new" );
	m_SnappingSign = scene->addRect( rc );
    }
    
}
