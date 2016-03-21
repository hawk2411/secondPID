#ifndef __RCRECTANGLECREATOR_H__
#define __RCRECTANGLECREATOR_H__

class QMaindWindow;

/*! \brief a class for creating rectangles
 *
 */
class RectangleCreator : public GraphicsItemCreator
{
public:
    RectangleCreator();
    ~RectangleCreator();

   void paint ( QPainter * painter, const QStyleOptionGraphicsItem*, QWidget* = 0 );
    QRectF boundingRect () const;
    
    void mouseMoveEvent ( QGraphicsSceneMouseEvent * mouseEvent );
    void mousePressEvent ( QGraphicsSceneMouseEvent * mouseEvent );
    bool endCreation();
protected:

private:
    QRectF m_rectangle;
    QPointF m_origin;
    bool m_rubber_mode;
};

#endif //__RCRECTANGLECREATOR_H__
