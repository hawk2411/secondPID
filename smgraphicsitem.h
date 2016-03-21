#ifndef __RCSMGRAPHICSITEM_H__
#define __RCSMGRAPHICSITEM_H__

#include "snapmode.h"

class SMGraphicsItem : public SnapMode
{
public:
    SMGraphicsItem();
    ~SMGraphicsItem();

    QPointF getSnapPoint( GraphicsScene * scene, const QPointF& not_aligned_pt );

    void setSign( GraphicsScene* scene, const QPointF& nearest_point );
    //void setSnapDistance( qreal newVal ){ m_snapDistance = newVal; }
    //qreal getSnapDistance()const{ return m_snapDistance; }

protected:

private:
    qreal m_snapDistance;
};

#endif //__RCSMGRAPHICSITEM_H__
