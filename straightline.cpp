#include <math.h>

#include "straightline.h"


/*
	constructor /destructor
*/
StraightLine::StraightLine()
{

}
StraightLine::StraightLine( const RCPoint& pt1, const RCPoint& pt2 )
{
    m_pt1 = pt1;
    m_pt2 = pt2;
}

StraightLine::~StraightLine()
{

}

qreal StraightLine::getDistance(const RCPoint& pt )const
{
    RCPoint lineV = getDirectionVector();
    RCPoint v1 = pt - m_pt1;
    RCPoint v2 = v1.crossProduct( lineV );
    RCPoint v3 = v2.crossProduct( lineV );

    RCPoint direction = v3.getDirection( RCPoint(0.0, 0.0, 0.0) );
    
    qreal ret_value = fabs(v1 * direction);

    return ret_value;
}

qreal StraightLine::getLength()const
{
    RCPoint pt = m_pt1 - m_pt2;
    
    return pt.getLength();
}

RCPoint StraightLine::getDirectionVector()const
{
    RCPoint ret_value;
    RCPoint pt = m_pt1 - m_pt2;
    qreal length = pt.getLength();

    ret_value.setX(pt.x() / length);
    ret_value.setY(pt.y() / length);

    return ret_value;
}

RCPoint StraightLine::getCrossPoint(const RCPoint& pt)const
{
    RCPoint lineV = getDirectionVector();
    RCPoint v1 = pt - m_pt1;
    RCPoint v2 = v1.crossProduct( lineV );
    RCPoint v3 = v2.crossProduct( lineV );
    
    RCPoint cross_point = pt+v3;

    return cross_point;
}
