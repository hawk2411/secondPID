#ifndef __RCSTRAIGHTLINE_H__
#define __RCSTRAIGHTLINE_H__

#include "point.h"

class StraightLine
{
public:
    StraightLine();
    StraightLine( const RCPoint& pt1, const RCPoint& pt2 );

    ~StraightLine();
    void setPoints( const RCPoint& pt1, const RCPoint& pt2){ m_pt1 = pt1; m_pt2=pt2; }
    qreal getDistance(const RCPoint& pt )const;
    RCPoint getCrossPoint(const RCPoint& pt)const;
    RCPoint getDirectionVector()const;
    qreal getLength()const;
protected:

private:
    RCPoint m_pt1, m_pt2;
};

#endif //__RCSTRAIGHTLINE_H__
