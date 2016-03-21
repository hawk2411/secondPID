#ifndef __RCGRAPHICSSCENE_H__
#define __RCGRAPHICSSCENE_H__

#include <QGraphicsScene>

#include "point.h"
#include "graphicsstyle.h"
#include "error.h"


class GraphicsItemCreator;
class GraphicsItem;
class QAction;
class GraphicsSceneMouseEvent;
class RCSnapModes;
class QRubberBand;

/*!
  enumeration of parameters for startCreationMode(...) function
*/
enum CreationModes
{
  None =0, /*!< kill current creation if one exists */
  Path = 1, /*!< creation mode for creating a line path */
  Circle = 2, /*!< creation mode for creatin a circle */
  Rectangle =3 /*!< creation mode for creatin a rectangle */
};

/*! \brief derived from QGraphicsScene this class contol a document
 *
 * this class itself derived from QGraphicsItem and provides some expedient 
 * functions for my program
 */

class GraphicsScene : public QGraphicsScene
{
	Q_OBJECT
public:
    GraphicsScene( QObject *parent = 0);
    GraphicsScene(  qreal x, qreal y, qreal width, qreal height, QObject * parent = 0 );
    virtual ~GraphicsScene();
    
	void addCreationItem( GraphicsItemCreator * pItem );
	QGraphicsItem * mouseGrabberItem () const;
  void removeItem(QGraphicsItem * item );
	bool changeCreationMode( CreationModes mode); ///throw(RCError*);
    
protected:
	void mousePressEvent ( QGraphicsSceneMouseEvent * mouseEvent );
	void mouseMoveEvent ( QGraphicsSceneMouseEvent * mouseEvent );
	void mouseReleaseEvent ( QGraphicsSceneMouseEvent * mouseEvent );
	void contextMenuEvent ( QGraphicsSceneContextMenuEvent * contextMenuEvent );
	void drawBackground ( QPainter * painter, const QRectF & rect );

	//members access functions
public:
	void addRCItem( GraphicsItem * newItem );
	qreal getGridX()const{return m_grid_x;}
	qreal getGridY()const{return m_grid_y;}
	void setSnapModes( RCSnapModes *pValue ){ m_SnapModes = pValue; }
	QPointF getAlignedPoint( const QPointF& not_aligned_pt );
	bool isSelectionMode()const{ return (m_pCreationItem == NULL ); }
protected:
	//functions for handling with rubber rect
	//bool startRubberRect( QGraphicsSceneMouseEvent* mouseEvent );
	//bool increaseRubberRect( QGraphicsSceneMouseEvent* mouseEvent );
	//bool endRubberRect();

	uint removeSelectedItems();
	bool executeAction( QAction * toExecute );
	//Members
public:
    GraphicsStyle style;
private:
	GraphicsItemCreator * m_pCreationItem;    //current item creator or NULL
	QList<GraphicsItem*> m_ItemsToDelete;      //container for created items, they have to be deleted in desctructor or on remove
	//QGraphicsRectItem * m_pRubberRectItem;      //initialized by startRubberRect   
	qreal m_grid_x;
	qreal m_grid_y;
	RCSnapModes * m_SnapModes;      /**< managed snap modes and the SnapMode ComboBox */

signals:
	void endItemCreation();
	void newRCItem( GraphicsItem *newItem );
	void removeRCItem( GraphicsItem *item );
	void changedCoordinates( const QPointF& );
};

#endif //__RCGRAPHICSSCENE_H__
