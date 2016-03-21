#ifndef __RCSMGRIDALIGNED_H__
#define __RCSMGRIDALIGNED_H__

#include "snapmode.h"

/*!
  RCSMGridAligned
  derived from RCSnapMode
 */
class SMGridAligned : public SnapMode
{
public:
    /*!
      sets the description of the. it will be seen in the combobox
     */
    SMGridAligned();
    ~SMGridAligned();
    
    /*!
      derived from RCSnapMode. Returns the nearest point of the grid
     */
    QPointF getSnapPoint( GraphicsScene * scene, const QPointF& not_aligned_pt );
    void setSign( GraphicsScene* scene, const QPointF& nearest_point );
protected:

private:

};

#endif //__RCSMGRIDALIGNED_H__
