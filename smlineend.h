#ifndef __RCSMLINEEND_H__
#define __RCSMLINEEND_H__

#include "snapmode.h"

/*! RCSMLineEnd
  derived from RCSnapMode. The class implements the snapping on line ends
 */
class SMLineEnd : public SnapMode
{
public:
    SMLineEnd();
    ~SMLineEnd();

    /// returns a modified/snapping point 
    QPointF getSnapPoint( GraphicsScene * scene, const QPointF& not_aligned_pt );

    void setSign( GraphicsScene* scene, const QPointF& nearest_point );
    void setSnapDistance( qreal newVal ){ m_snapDistance = newVal; }
    qreal getSnapDistance()const{ return m_snapDistance; }
    
private:
    qreal m_snapDistance;
};

#endif //__RCSMLINEEND_H__
