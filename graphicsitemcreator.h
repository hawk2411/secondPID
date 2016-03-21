#ifndef __RCGRAPHICSITEMCREATOR_H__
#define __RCGRAPHICSITEMCREATOR_H__

#include <QGraphicsItem>
#include "graphicsitem.h"
#include "snapmodes.h"

class QEvent;
class RCView;
class RCCreatorWidget;
class QMainWindow;

/*! RCGraphicsItemCreator
  main class for all creating classes
 */
class GraphicsItemCreator : public GraphicsItem
{
public:
    GraphicsItemCreator();
    virtual ~GraphicsItemCreator();

    virtual void paint ( QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = 0 ) =0;
    virtual QRectF boundingRect () const;
    
    virtual void mouseMoveEvent ( QGraphicsSceneMouseEvent * mouseEvent ) = 0 ;
    virtual void mousePressEvent ( QGraphicsSceneMouseEvent * mouseEvent ) = 0;
    virtual bool endCreation() = 0;

    //virtual RCCreatorWidget* getWidget(){return m_RCCreatorWidget; }
    //member variable
protected:
};

#endif //__RCGRAPHICSITEMCREATOR_H__
