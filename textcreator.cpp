#include "textcreator.h"


/*
	constructor /destructor
*/
TextCreator::TextCreator()
{

}
TextCreator::~TextCreator()
{

}

void TextCreator::paint ( QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget )
{
    Q_UNUSED(painter);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}

QRectF TextCreator::boundingRect () const
{
    return QRectF();
    //throw std::exception("not implemented");
}
    
void TextCreator::mouseMoveEvent ( QGraphicsSceneMouseEvent * mouseEvent )
{
    Q_UNUSED(mouseEvent);
}

void TextCreator::mousePressEvent ( QGraphicsSceneMouseEvent * mouseEvent )
{
    Q_UNUSED(mouseEvent);
}

bool TextCreator::endCreation()
{
  //throw std::exception("not implemented");
    return false;
}
