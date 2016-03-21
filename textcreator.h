#ifndef __RCTEXTCREATOR_H__
#define __RCTEXTCREATOR_H__

#include "graphicsitemcreator.h"

class TextCreator : GraphicsItemCreator
{
public:
    TextCreator();
    ~TextCreator();

    void paint ( QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = 0 );
    QRectF boundingRect () const;
    
    void mouseMoveEvent ( QGraphicsSceneMouseEvent * mouseEvent );
    void mousePressEvent ( QGraphicsSceneMouseEvent * mouseEvent );
    bool endCreation();

protected:

private:

};

#endif //__RCTEXTCREATOR_H__
