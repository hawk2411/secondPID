#ifndef RCGRAPHICSVIEW_H
#define RCGRAPHICSVIEW_H

#include <QGraphicsView>
#include <QRubberBand>

/** \brief own graphics view is useful
 *
 */
class GraphicsView : public QGraphicsView
{
public:
    GraphicsView(QWidget *parent);
    ~GraphicsView();
    

protected:
    void mousePressEvent(QMouseEvent *event);  
    void mouseMoveEvent ( QMouseEvent * event );    
    void mouseReleaseEvent ( QMouseEvent * event );
//    void drawItems ( QPainter * painter, int numItems, QGraphicsItem * items, const QStyleOptionGraphicsItem* options );
    
private:

    QRubberBand* m_pRubberBand;

};

#endif // RCGRAPHICSVIEW_H
