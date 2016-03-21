#include <QtCore/QRectF>
#include <QGraphicsItem>
#include <QListWidgetItem>
#include <math.h>

#include "global_defs.h"
#include "graphicsitem.h"
#include "graphicsscene.h"
#include "snapmodes.h"
#include "smlineend.h"


/*
	constructor /destructor
*/
SMLineEnd::SMLineEnd()
{
    m_snapDistance = DEF_SNAP_WIDTH;
    m_Description = "line ends";

    //m_ListItem = new QListWidgetItem;
    m_ListItem->setText( m_Description );
    m_ListItem->setFlags( Qt::ItemIsSelectable|Qt::ItemIsUserCheckable|Qt::ItemIsEnabled);
    m_ListItem->setCheckState( Qt::Unchecked );
    m_ListItem->setData( Qt::UserRole, QVariant((int)snap_by_line_end));

}
SMLineEnd::~SMLineEnd()
{
}
/** creates a rectangle round the point and gets from scene all items the rectangle hits. The nearest node of item
 * is the snap mode
 */
QPointF SMLineEnd::getSnapPoint( GraphicsScene * scene, const QPointF& not_aligned_pt )
{
    const int rect_width = m_snapDistance;

    QRectF rc;
    const double half = rect_width/2;
    QList<QGraphicsItem*> litems;
    mouse_points_t nodes;
    GraphicsItem *item;
    QPointF nearest_point, pt;
    qreal d, smallest_d = 10000000000000.0;

    //construct a square
    rc.setLeft( not_aligned_pt.x() - half );
    rc.setWidth( rect_width );
    rc.setTop( not_aligned_pt.y() -half );
    rc.setHeight( rect_width );
    
    //get items intersect the rectangle
    litems = scene->items( rc );
    if( litems.size() < 1 )
    {
	return not_aligned_pt;
    }
    else
    {
	for( int i=0; i < litems.size(); i++)
	{
	    item = dynamic_cast<GraphicsItem*>(litems[i]);
	    if( item != NULL )
	    {
		EdgeSnap *edge = dynamic_cast<EdgeSnap*>(item);
		QPointF item_nearest_point;

		if( edge != NULL )
		{
		    edge->setSnapDistance( m_snapDistance );
		    if( edge->getNearestEdgePoint(not_aligned_pt, item_nearest_point))
		    {
			RCPoint rcpt = item_nearest_point;
			d = rcpt.getDistance( not_aligned_pt );
			if( d < smallest_d )
			{
			    smallest_d = d;
			    nearest_point = rcpt;
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
	else
	{
	    removeSign();
	    return not_aligned_pt;
	}
    }
}

void SMLineEnd::setSign( GraphicsScene* scene, const QPointF& nearest_point )
{
    QRectF rc( nearest_point.x()-10, nearest_point.y()-10, 20, 20 );

    if( ( m_SnappingSign != NULL ) &&  (m_SnappingSign->boundingRect() != rc) )
    {
	removeSign();
	m_SnappingSign = scene->addEllipse( rc );
    }
    else if( m_SnappingSign == NULL )
    {
	qDebug( "set new" );
	m_SnappingSign = scene->addEllipse( rc );
    }
    
}
