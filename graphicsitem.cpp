#include <QPainter>
#include <QDate>
#include <QLocale>
//#include <Qt/qtpropertymanager.h>
//#include <Qt/qtvariantproperty.h>
//#include <Qt/qttreepropertybrowser.h>

#include "graphicsscene.h"
#include "graphicsitem.h"


/*
	constructor /destructor
*/

GraphicsItem::GraphicsItem(QGraphicsItem * parent, QGraphicsScene * scene)
    :QGraphicsItem(parent)
{
    Q_UNUSED(scene);
    m_sType = "undefined";

}
GraphicsItem::~GraphicsItem()
{

}

/*void RCGraphicsItem::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
}*/

void GraphicsItem::paint( QPainter * painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    
    if( painter->isActive() )
    {
	if( isSelected() )
	{
	    GraphicsScene* pScene;
	    pScene = (GraphicsScene*)scene();
	    if( pScene != NULL )
	    {
		painter->setPen(pScene->style.m_penSelection );
	    }

	}
    }

}

mouse_points_t GraphicsItem::getNodes()const
{
    mouse_points_t ret_val;

    return ret_val; //return just an empty vector
}
mouse_points_t GraphicsItem::getCenterNodes()const
{
    mouse_points_t ret_val;

    return ret_val; //return just an empty vector
}

bool GraphicsItem::collidesWithPath ( const QPainterPath & path, Qt::ItemSelectionMode) const
{
    
	int i;
	mouse_points_t nodes = getNodes();
	int nsize = nodes.size();

	for( i=0; i < nsize-1; i++)
	{
		QPainterPath line;

		line.moveTo( nodes[i] );
		line.lineTo( nodes[i+1] );
		if( line.intersects( path ) )
		{
			return true;
		}
	}

	return false;
}
